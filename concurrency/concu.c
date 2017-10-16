//
// Created by shiyang on 9/7/17.
//


#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>


//int num __attribute__ ((aligned(CACHE_LINE_SIZE))) = 0;

typedef struct {
    long long *elems;
    int *idx;
    int elems_size;
} elems_info_t;

typedef struct {
    FILE *file;
    int id;
    int *myTurn;
    pthread_cond_t *cond;
    pthread_mutex_t *mutex;
    elems_info_t elem_info;
} info_t; // __attribute__((__packed__))


#define print_err(msg) do { perror(msg); exit(0);} while(0)


void info_init(info_t *info, int id, FILE *file, int *myTurn, pthread_cond_t *cond, pthread_mutex_t *mutex) {
    info->id = id;
    info->file = file;
    info->myTurn = myTurn;
    info->mutex = mutex;
    info->cond = cond;
}

int produce_elems(const char *file_name);

void *consumer(void *arg);


#define ELEMS_SIZE  10000
#define PRINT_EACH_TIME 10

long long odd_elems[ELEMS_SIZE];
long long even_elems[ELEMS_SIZE];

int odd_size = 0;
int even_size = 0;

int finish_count = 0;
int even_idx = 0;
int odd_idx = 0;


int main(int argc, char *argv[]) {

    if (argc != 7) {
        fprintf(stderr, "usage : %s filenames ...\n", argv[0]);
        exit(0);
    }
    produce_elems(argv[1]);
    pthread_t tids[10];
    printf("1\n");
    for (int i = 0; i < 5; ++i) {

        pthread_mutex_t *mutex = (pthread_mutex_t *) malloc(sizeof(pthread_mutex_t));
        pthread_cond_t *cond = (pthread_cond_t *) malloc(sizeof(pthread_cond_t));
        pthread_mutex_init(mutex, NULL);
        pthread_cond_init(cond, NULL);

        int *myTurn = (int *) malloc(sizeof(int));
        *myTurn = 0;


        FILE *file = fopen(argv[i + 2], "a+");

        if (file == NULL) { print_err("fopen err"); }

        for (int j = 0; j < 2; ++j) {
            info_t *info = (info_t *) malloc(sizeof(info_t));
            if (j == 1) {
                info->elem_info.idx = &odd_idx;
                info->elem_info.elems_size = odd_size;
                info->elem_info.elems = odd_elems;
            } else {
                info->elem_info.idx = &even_idx;
                info->elem_info.elems_size = even_size;
                info->elem_info.elems = even_elems;
            }

            info_init(info, i * 2 + j, file, myTurn, cond, mutex);

            if (pthread_create(&tids[i * 2 + j], NULL, consumer, (void *) info) != 0) {
                print_err("pthread_create err");
            }
        }
    }

    for (int i = 0; i < 10; ++i) {
        if (pthread_join(tids[i], NULL) != 0) {
            print_err("pthread_join err");
        }
    }

    printf("Done.\n");
    return 0;
}


void *consumer(void *arg) {

    info_t *info = (info_t *) (arg);
    bool done = false;
    while (!done) {
        //  printf("hehe;");
        if (pthread_mutex_lock(info->mutex) != 0) {
            print_err("pthread_mutex_lock err");
        }
        // when *info->myTurn < 0, it means the other thread is done, there is no race condition
        //syn is unneccesary and false, as nobody else can wake you up
        while (*info->myTurn >= 0 && (*(info->myTurn) & 1) != (info->id & 1)) {
            printf("%d wait, turn = %d\n", info->id, *info->myTurn);
            if (pthread_cond_wait(info->cond, info->mutex) != 0) {
                print_err("pthread_cond_wait err");
            }
        }

        int start;
        if ((start = __sync_fetch_and_add(info->elem_info.idx, 10)) < info->elem_info.elems_size) {

            int end = start + 10;
            if (end >= info->elem_info.elems_size) {
                end = info->elem_info.elems_size;
                done = true;
            }

            for (int i = start; i != end; ++i) {
                fprintf(info->file, "%lld ", info->elem_info.elems[i]);
            }

            int val = __sync_add_and_fetch(&finish_count, end - start);
            if (!(val % 100)) {
                printf("have finish : %d\n", val);
            }
        } else {
            done = true;
        }
        if (*info->myTurn >= 0)
            *info->myTurn = *info->myTurn ? 0 : 1;
        if (done == true) {
            *info->myTurn = -1;
            printf("id = %d, myTurn = %d\n", info->id, *info->myTurn);
        }
        pthread_cond_broadcast(info->cond);
        if (pthread_mutex_unlock(info->mutex) != 0) {
            print_err("pthread_mutex_unlock err");
        }
    }
    printf("id = %d done, the finish_count = %d \n", info->id, finish_count);
    return NULL;
}


int produce_elems(const char *file_name) {

    FILE *file = fopen(file_name, "r");

    long long elem;
    while (fscanf(file, "%lld", &elem)) {

        if (elem & 1) {
            odd_elems[odd_size++] = elem;
        } else {
            even_elems[even_size++] = elem;
        }

    }

    printf("%d %d\n", odd_size, even_size);

    return odd_size + even_size;
}



















