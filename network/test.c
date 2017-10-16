//
// Created by shiyang on 9/5/17.
//
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include <memory.h>

typedef struct {
    int isEven;
    int fd;
    int *myTurn;
    pthread_cond_t *cond;
    pthread_mutex_t *mutex;
} info_t;// __attribute__((__packed__))


typedef struct {
    int head;
    int tail;
    int total_elems;
    long long elem[10000];
    pthread_mutex_t mutex;
    pthread_cond_t empty_cond;
    pthread_cond_t full_cond;
} block_queue_t;


#define print_err(msg) \
    do { perror(msg); exit(0);} while(0)


void block_queue_init(block_queue_t *queue);
void block_queue_destroy(block_queue_t *queue); // todo

int consume_elems(long long elem[], int size);
int produce_elems(FILE *file);
void *consumer(void *arg);
void *producer(void *arg);

inline bool has_k_empty_slots(block_queue_t *queue, int size) {  return 1024 - queue->total_elems >= size; }
inline bool has_k_elems(block_queue_t *queue, int size) { return queue->total_elems >= size; }



#define ELEMS_SIZE  1000000
#define PRINT_EACH_TIME 10

int finish_count = 0;

block_queue_t *block_queue;

int main(int argc, char *argv[]) {

    if (argc != 2) {

    }

    pthread_t tid[10];

    for (int i = 0; i < 5; ++i) {

        for (int j = 0; j < 2; ++j) {

        }
    }

    for (int i = 0; i < 10; ++i) {
        if (pthread_join(tid[i], NULL) != 0) {
            print_err("pthread_join err");
        }
    }

    printf("Done.\n");
    return 0;
}


void block_queue_init(block_queue_t *queue) {
    queue->head = 0;
    queue->tail = 0;
    queue->total_elems = 0;
    if (pthread_mutex_init(&queue->mutex, NULL) != 0) {
        print_err("pthread_mutex_init err");
    }

    if (pthread_cond_init(&queue->empty_cond, NULL) != 0) {
        print_err("pthread_mutex_cond err");
    }

    if (pthread_cond_init(&queue->full_cond, NULL) != 0) {
        print_err("pthread_mutex_cond err");
    }
}


void *consumer(void *arg) {
    info_t *info = (info_t *) (arg);
    int elems[PRINT_EACH_TIME];
    while ((finish_count  = __sync_fetch_and_add(&finish_count, PRINT_EACH_TIME) <= ELEMS_SIZE)) {

        if (finish_count % 1000 == 0) {
            printf("finish_count = %d\n", finish_count);
        }
    }

    return NULL;
}

void *producer(void *arg) {
    const char *file_name = (const char *) arg;

    FILE *file = fopen(file_name, "r");

    printf("before produce\n");
    produce_elems(file);
    printf("after produce\n");

    return NULL;
}

int consume_elems(long long elem[], int size) {

    if (pthread_mutex_lock(&block_queue->mutex) != 0) {
        print_err("pthread_mutex_lock err");
    }

    // if the queue has w ( 0 < w < size) elements in the end, may lead to dead lock
    while (has_k_elems(block_queue, size) == false) {
        if (pthread_cond_wait(&block_queue->empty_cond, &block_queue->mutex) != 0) {
            print_err("pthread_cond_wait err");
        }
    }

    memcpy(elem, &block_queue->elem[block_queue->head], size * sizeof(long long));

    block_queue->head = (block_queue->head + size) % 1024;
    block_queue->total_elems -= size;

    if (pthread_cond_broadcast(&block_queue->full_cond) != 0) {
        print_err("pthread_cond_broadcast err");
    }
    if (pthread_mutex_unlock(&block_queue->mutex) != 0) {
        print_err("pthread_mutex_unlock err");
    }

    return size;
}

int produce_elems(FILE *file) {

    long long elem[128];

    while (!feof(file)) {
        int size = 0;
        while (fscanf(file, "%lld", &elem[size++]) != EOF && size < 128);

        if (pthread_mutex_lock(&block_queue->mutex) != 0) {
            print_err("pthread_mutex_lock err");
        }

        // if the queue has w ( 0 < w < size) elements in the end, may lead to dead lock
        while (has_k_empty_slots(block_queue, size) == false) {
            if (pthread_cond_wait(&block_queue->full_cond, &block_queue->mutex) != 0) {
                print_err("pthread_cond_wait err");
            }
        }

        memcpy(elem, &block_queue->elem[block_queue->tail], size * sizeof(long long));

        block_queue->tail = (block_queue->tail + size) % 1024;
        block_queue->total_elems += size;

        if (pthread_cond_broadcast(&block_queue->empty_cond) != 0) {
            print_err("pthread_cond_broadcast err");
        }

        if (pthread_mutex_unlock(&block_queue->mutex) != 0) {
            print_err("pthread_mutex_unlock err");
        }
    }
    return -1;
}



















