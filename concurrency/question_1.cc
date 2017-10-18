//
// Created b_y shiyang on 9/10/17.
//

#include <pthread.h>
#include <iostream>
#include "net.h"
using namespace std;


#define THREADS_NUM  4
#define FILE_LEN 20
char file_name[] = "?.txt";

FILE* streams[THREADS_NUM];

const char letters[] = {'A', 'B', 'C', 'D'};
int write_files_turn[] = {0, 1, 2, 3};

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;


void *fun(void *msg) {

    auto id = (long long) msg;

    for (int file_len = 0; file_len < FILE_LEN; ++file_len) {
        for (int idx = 0 ;idx < THREADS_NUM; ++idx) {
            int& turn = write_files_turn[idx];
            pthread_mutex_lock(&mutex);

            while (turn != id) {
                pthread_cond_wait(&cond, &mutex);
            }

            fprintf(streams[idx], "%c", letters[id]);
            write_files_turn[idx] = (turn + 1) % THREADS_NUM;

            pthread_cond_broadcast(&cond);
            pthread_mutex_unlock(&mutex);
        }
    }

    return nullptr;
}


void main() {
    for (int i = 0; i < THREADS_NUM; ++i) {
        file_name[0] = ('0' + i);
        if ((streams[i] = fopen(file_name, "w+")) == NULL) {
            print_err("fopen err");
        }
    }

    pthread_t tid[THREADS_NUM - 1];

    for (int i = 0 ;i < THREADS_NUM - 1;++i) {
        pthread_create(&tid[i], NULL, fun, (void*)i);
    }

    fun((void*)3);

    for (int i = 0 ;i < THREADS_NUM - 1;++i) {
        pthread_join(tid[i], NULL);
    }

    return 0;
}