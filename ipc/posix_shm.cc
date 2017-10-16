//
// Created by shiyang on 10/7/17.
//


#include <stdlib.h>
#include <pthread.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <unistd.h>
#include <assert.h>
#include <new>
#include "Util.h"

class Mutex {
public:
    virtual void lock() = 0;

    virtual void unlock() = 0;

    Mutex() = default;

    Mutex(const Mutex &) = delete;

    const Mutex &operator=(const Mutex &) = delete;

protected:
    pthread_mutex_t mutex;
};


class SharedMutex final : public Mutex {
public:
    SharedMutex() { init(); }

    ~SharedMutex() { destroy(); }

    void lock() {
        PCHECK(pthread_mutex_lock(&mutex));
    }

    void unlock() {
        PCHECK(pthread_mutex_unlock(&mutex));
    }

protected:
    pthread_mutexattr_t mutexAttr;

    void init() {
        PCHECK(pthread_mutexattr_init(&mutexAttr));
        PCHECK(pthread_mutexattr_setpshared(&mutexAttr, PTHREAD_PROCESS_SHARED));
        PCHECK(pthread_mutex_init(&mutex, &mutexAttr));
    }

    void destroy() {
        PCHECK(pthread_mutexattr_destroy(&mutexAttr));
        PCHECK(pthread_mutex_destroy(&mutex));
    }
};

class LockGuard {
public:
    LockGuard(Mutex &mutex) : mutex(mutex) {
        mutex.lock();
    }

    ~LockGuard() {
        mutex.unlock();
    }

private:
    Mutex &mutex;
};

template<typename T, int size>
class SharedMemoryStack {
public:
    SharedMemoryStack() : idx(0), threads_count(1) {}

    void push(const T &t) {
        LockGuard lock(mutex);
        assert(idx < size);
        _stack[idx++] = t;
    }

    void pop() {
        LockGuard lock(mutex);
        assert(idx > 0);
        --idx;
    }

    bool empty() {
        LockGuard lock(mutex);
        return idx == 0;
    }

    T top() {
        LockGuard lock(mutex);
        assert(idx > 0);
        return _stack[--idx];
    }

    void checkIn() {
        LockGuard lock(mutex);
        ++threads_count;
    }

    void checkOut() {
        LockGuard lock(mutex);
        // ? todo
        // how to destroy mutex??
    }

    void destroy() {

    }

private:
    SharedMutex mutex;
    T _stack[size];

    int idx;
    int threads_count;
};


void main() {
    int shm_fd = shm_open("shm", O_CREAT | O_RDWR, S_IRWXU);
    CHECK(shm_fd >= 0);
    CHECK(ftruncate(shm_fd, sizeof(SharedMutex)) == 0);

    void *shm_ptr = mmap(NULL, sizeof(SharedMutex), PROT_READ | PROT_WRITE, MAP_SHARED, shm_fd, 0);
    CHECK(shm_ptr != NULL);
    SharedMutex *sharedMutex = new(shm_ptr) SharedMutex;
    sharedMutex->lock();

    if (fork() == 0) { //  child process does not hold the lock,which means it does not inherit the status of the lock
        sharedMutex->lock();

        printf("Hello world\n");
        goto DONE;
    }
    // sharedMutex->unlock();

    printf("main done\n");
    DONE:
    return 0;
}
