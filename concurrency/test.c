//
// Created b_y shiyang on 9/7/17.
//

#include <pthread.h>
#include <stdio.h>

int turn;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

typedef struct {
    int myTurn;
    int num;
}info_t;

void* thread(void* arg) {

    info_t* info = (info_t*)(arg);

    for (int i = 0; i < 50; ++i) {
        pthread_mutex_lock(&mutex);
        while (turn >= 0 && info->myTurn != turn) {
            pthread_cond_wait(&cond, &mutex);
        }
        for (int j = 0; j < info->num; ++j) {
            printf("%d ", info->myTurn);
        }

        if (i == 49) {
            turn = -1;
        } else {
            turn = info->myTurn ? 0 : 1;
        }

        printf("\n");
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }

    return NULL;
}

void main() {
    pthread_t tid;
    info_t info[2] = {{0, 10}, {1, 100}};
    turn = 0;
    pthread_create(&tid, NULL, thread, (void*)info);
    thread((void*)(info + 1));
    pthread_join(tid, NULL);
    return 0;
}