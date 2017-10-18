//
// Created b_y shiyang on 9/4/17.
//

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ERR -1

typedef struct {
    pthread_mutex_t mutex;
    pthread_cond_t wr_cond;
    pthread_cond_t rd_cond;
    int rd_count;
    int wr_count;
} rw_lock_t;

void rw_lock_init(rw_lock_t *rw_lock) {
    rw_lock->rd_count = 0;
    rw_lock->wr_count = 0;

    pthread_mutex_init(&rw_lock->mutex, NULL);
    pthread_cond_init(&rw_lock->rd_cond, NULL);
    pthread_cond_init(&rw_lock->wr_cond, NULL);
}

void rw_lock_destroy(rw_lock_t* rw_lock) {
    //todo
}

int rwlock_rlock(rw_lock_t *rw_lock) {

    pthread_mutex_lock(&rw_lock->mutex);

    while (rw_lock->wr_count != 0) {
        pthread_cond_wait(&rw_lock->rd_cond, &rw_lock->mutex);
    }
    ++rw_lock->rd_count;
    pthread_mutex_unlock(&rw_lock->mutex);
    return OK;
}

int rwlock_wlock(rw_lock_t *rw_lock) {

    pthread_mutex_lock(&rw_lock->mutex);

    while (rw_lock->rd_count != 0 && rw_lock->wr_count != 0) {
        pthread_cond_wait(&rw_lock->wr_cond, &rw_lock->mutex);
    }

    ++rw_lock->wr_count;
    pthread_mutex_unlock(&rw_lock->mutex);
    return OK;
}

int rwlock_runlock(rw_lock_t *rw_lock) {
    pthread_mutex_lock(&rw_lock->mutex);
    int ret = OK;
    if (rw_lock->rd_count <= 0) {
        ret = ERR;
        pthread_cond_signal(&rw_lock->wr_cond);
        goto DONE;
    }

    if (--rw_lock->rd_count == 0) {
    }

DONE:
    pthread_mutex_unlock(&rw_lock->mutex);
    return ret;
}

int rwlock_wunlock(rw_lock_t *rw_lock) {
    pthread_mutex_lock(&rw_lock->mutex);
    int ret = OK;
    if (rw_lock->wr_count <= 0) {
        ret = ERR;
        goto DONE;
    }
    --rw_lock->wr_count;
    pthread_cond_broadcast(&rw_lock->rd_cond); // use broadcast
    pthread_cond_signal(&rw_lock->wr_cond);
DONE:
    pthread_mutex_unlock(&rw_lock->mutex);
    return ret;
}


rw_lock_t rw_lock;

int val = 0;

void* read(void* arg) {
    long id = (long) arg;
    for (int i = 0; i < 10; ++i) {
        rwlock_rlock(&rw_lock);
        printf("reader %d reads val = %d\n", id, val);
        rwlock_runlock(&rw_lock);
    }
    printf("reader %d done.\n", id);
}

void* write(void* arg) {
    long id = (long) arg;
    for (int i = 0; i < 10; ++i) {
        rwlock_wlock(&rw_lock);
        ++val;
        printf("writer %d write val to %d\n", id, val);
        rwlock_wunlock(&rw_lock);
    }
    printf("writer %d done.\n", id);
}


void main() {
    rw_lock_init(&rw_lock);

    pthread_t readers[10];
    for (int i = 0; i < 10; ++i) {
        if (pthread_create(readers + i, NULL, read, (void*)i) != 0) {
            perror("pthread_create err");
            exit(0);
        }
    }

    pthread_t writers[2];
    for (int i = 0; i < 2; ++i) {
        if (pthread_create(writers + i, NULL, write, (void*)i) != 0) {
            perror("pthread_create err");
            exit(0);
        }
    }

    for (int i = 0; i < 10; ++i) {
        pthread_join(readers[i], NULL);
    }

    for (int i = 0; i < 2; ++i) {
        pthread_join(writers[i], NULL);
    }

    rw_lock_destroy(&rw_lock);

    return 0;
}
