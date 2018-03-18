#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>

#include <new>
#include <iostream>

#include "Util.h"


class Mutex {
public:
    virtual  void lock() = 0;
    virtual  void unlock() = 0;
    Mutex() = default; 
    Mutex(const Mutex&) = delete;
    const Mutex& operator=(const Mutex&) = delete;

protected:
    pthread_mutex_t mutex;
};


class PrivateMutex final : public Mutex {
public:
    PrivateMutex()  { init(); }
    ~PrivateMutex() { destroy(); }
    void lock() {   PCHECK(pthread_mutex_lock(&mutex));  }
    void unlock() { PCHECK(pthread_mutex_unlock(&mutex)); }

protected:
    void init() { PCHECK(pthread_mutex_init(&mutex, NULL)); }
    void destroy() { PCHECK(pthread_mutex_destroy(&mutex)); }
};

class LockGuard {
public:
    LockGuard(Mutex& mutex) : mutex(mutex) { mutex.lock(); }
    ~LockGuard() { mutex.unlock(); }
    
private:
    Mutex& mutex;
};

PrivateMutex privateMutex; 

void* func(void* ptr) {
    privateMutex.lock();
    return nullptr;
}


/* method :
            ./a.out &
            killall -11 a.out
            gdb ./a.out xxx.xxx.xxx.core
 */ 


void checkPoint() {
    static int pointerCount = 0;
    std::cout << "point" << ++pointerCount << std::endl;
    
}

int main() {
    pthread_t tid[2];
    
    checkPoint();
    
    for (int i = 0; i < 2; ++i) {
        sleep(1);
        checkPoint();
        PCHECK(pthread_create(tid + i, NULL, func, NULL));
    }

    pthread_join(tid[0], NULL);
    pthread_join(tid[1], NULL);
    
    return 0;
}