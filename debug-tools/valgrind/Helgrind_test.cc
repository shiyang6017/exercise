//
// Created by shiyang on 10/11/17.
//



#include <pthread.h>
#include <iostream>

using namespace std;


pthread_mutex_t mutex_a =  PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex_b =  PTHREAD_MUTEX_INITIALIZER;





int i = 0;

void* fun_ab(void* arg) {

    i++; // print possible race condition

    pthread_mutex_lock(&mutex_a); //  print lock order "0x601070 before 0x601098" violated
    pthread_mutex_lock(&mutex_b);

    pthread_mutex_unlock(&mutex_b);
    pthread_mutex_unlock(&mutex_a);

    return nullptr;
}

void* fun_ba(void* arg) {

    i++;

    pthread_mutex_lock(&mutex_b);
    pthread_mutex_lock(&mutex_a);

    pthread_mutex_unlock(&mutex_a);
    pthread_mutex_unlock(&mutex_b);

    return nullptr;
}

void main() {

    pthread_t tid[2];

    pthread_create(tid, nullptr, fun_ab, nullptr);
    pthread_create(tid + 1, nullptr, fun_ba, nullptr);


    pthread_join(tid[0], nullptr);
    pthread_join(tid[1], nullptr);
    return 0;
}




