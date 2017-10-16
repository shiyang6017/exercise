#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlockattr_t attr;
    
pthread_rwlock_t rwlock;

static int count = 0;

void* read_func(void* arg) {
    long long sec = reinterpret_cast<long long>(arg);
    pthread_rwlock_rdlock(&rwlock);
    printf("%lld\n", sec);
    sleep( sec);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void* write_func(void* arg) {
    long long sec = reinterpret_cast<long long>(arg);
    pthread_rwlock_wrlock(&rwlock);
    printf("%lld\n", sec);
    sleep(sec);
    pthread_rwlock_unlock(&rwlock);
    return NULL;
}

void main() {
    pthread_rwlockattr_init(&attr);
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP); // write first
    
    //pthread_rwlockattr_setkind_np (&attr, PTHREAD_RWLOCK_PREFER_READER_NP); // default: read first
    
    pthread_rwlock_init(&rwlock, &attr);
    pthread_t tid[3];
    pthread_create(&tid[0], NULL, read_func, reinterpret_cast<void*>(1));
    usleep(100);
    pthread_create(&tid[1], NULL, write_func, reinterpret_cast<void*>(2));
    usleep(100);
    pthread_create(&tid[2], NULL, read_func, reinterpret_cast<void*>(3));
    
    for (int i = 0; i < 3; ++i) {
        pthread_join(tid[i], NULL);
    }
    
    return 0;
}