//
// Created b_y shiyang on 9/10/17.
//
#include <pthread.h>
#include <cstdio>
#include "net.h"


#define SIZE (1 << 10)
#define THREAD_NUM 4

int buf[SIZE];

long long sum2 = 0;
int idx = 0;
pthread_barrier_t barrier;

void* fun(void* msg) {

    int calc_once = 100;
    int start_idx;

    while (( start_idx = __sync_fetch_and_add(&idx, calc_once)) < SIZE) {
        int end_idx = start_idx + calc_once;
        if (unlikely(end_idx >= SIZE)) {
            end_idx = SIZE;
        }
        int tmp_sum = 0;
        for (int i = start_idx; i < end_idx; ++i) {
            tmp_sum += buf[i];
        }
        __sync_fetch_and_add(&sum2, tmp_sum);
    }

   // pthread_barrier_wait(&barrier);

    printf("thread %lld done \n", (long long)msg);

    return NULL;
}


void main() {

    long long sum = 0;

    for (int i = 0; i < SIZE; ++i) {
        buf[i] = i;
        sum += i;
    }
    printf("sum = %lld\n", sum);
  //  pthread_barrier_init(&barrier, NULL, THREAD_NUM);

    pthread_t tids[THREAD_NUM - 1];
    for (int i = 0; i < THREAD_NUM - 1; ++i) {
        pthread_create(&tids[i], NULL, fun, (void*)i);
    }
    fun((void*)(THREAD_NUM - 1));

   // pthread_barrier_destroy(&barrier);
    for (int i = 0; i < THREAD_NUM - 1; ++i) {
        pthread_join(tids[i],NULL);
    }
    printf("%lld\n", sum2);
}