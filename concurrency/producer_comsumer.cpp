//
// Created b_y shiyang on 9/7/17.
//

#include <stdio.h>
#include <pthread.h>
#include <queue>
#include <stdlib.h>
#include <memory>
#include <string>
#include <iostream>

#define print_err(msg) do { perror(msg); exit(0);} while(0)



class Noncopyable {
public:
    Noncopyable() = default;
    ~Noncopyable() = default;
    const Noncopyable& operator=(const Noncopyable&) = delete;
    Noncopyable(Noncopyable&) = delete;
};

template <typename T, int size>
class BlockedQueue: Noncopyable {
    using  size_type = typename std::queue<T>::size_type;
public:
    BlockedQueue() {
        if (pthread_mutex_init(&mutex, nullptr)) {
            print_err("pthread_mutex_init err");
        }
        if (pthread_cond_init(&cond, nullptr)) {
            print_err("pthread_cond_init err");
        }
    }

    bool isFull() {

    }

    bool isEmpty() {

    }

    void push(T t) {
        if (pthread_mutex_lock(&mutex)) {
            print_err("pthread_mutex_lock err");
        }
        while (blockedQueue.size() >= QUEUE_SIZE) {
            if (pthread_cond_wait(&cond, &mutex)) {
                print_err("pthread_cond_wait err");
            }
        }

        blockedQueue.push(std::forward<T>(t));

        if (pthread_cond_signal(&cond) ) {
            print_err("pthread_cond_signal err");
        }

        if (pthread_mutex_lock(&mutex)) {
            print_err("pthread_mutex_unlock err");
        }
    }

    T pop() {
        if (pthread_mutex_lock(&mutex)) {
            print_err("pthread_mutex_lock err");
        }
        while (blockedQueue.empty()) {
            if (pthread_cond_wait(&cond, &mutex)) {
                print_err("pthread_cond_wait err");
            }
        }
        T ret = blockedQueue.front();
        blockedQueue.pop();
        if (pthread_cond_signal(&cond)) {
            print_err("pthread_cond_signal err");
        }
        if (pthread_mutex_lock(&mutex)) {
            print_err("pthread_mutex_unlock err");
        }
        return ret;
    }

private:
    std::queue<T> blockedQueue;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    static const size_type QUEUE_SIZE = static_cast<size_type >(size);
};

using namespace std;

void main() {
  //  shared_ptr<int> elem = new shared_ptr<int>( new int(1));
  //  cout << elem.use_count() << endl;
    string str("Hello World");
    BlockedQueue<string, 128> queue;
    queue.push(std::move(str));
    cout << str.size() << endl;
}