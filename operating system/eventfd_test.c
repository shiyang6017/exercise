//
// Created by shiyang on 9/18/17.

#include <sys/eventfd.h>
#include <sys/epoll.h>

#include "net.h"


// totally ignore return-value check

void fun(int event_fd) {
    int epoll_fd = epoll_create1(EPOLL_CLOEXEC); // EPOLL_NONBLOCK
    struct epoll_event event;
    const int SIZE = 1024;
    struct epoll_event ready_events[SIZE];
    int ready_nums;

    memset(&event, 0, sizeof event);
    event.events = EPOLLIN;
    event.data.fd = event_fd;

    epoll_ctl(epoll_fd, EPOLL_CTL_ADD, event_fd, &event);


    for (;;) {
        ready_nums = epoll_wait(epoll_fd, ready_events, SIZE, -1);
        for (int i = 0; i < ready_nums; ++i) {
            int fd = ready_events[i].data.fd;
            if (fd == event_fd) {
                uint64_t val;
                read(fd, &val, sizeof val);
                printf("the value of val = %lu\n", val);
            }
        }
    }
}

void main() {

    int event_fd = eventfd(0, EFD_NONBLOCK);

    pid_t child_pid;
    uint64_t val = 1314;
    if ((child_pid = fork()) == 0) {
        write(event_fd, &val, sizeof val);
        goto DONE;
    } else if (child_pid > 0) {
        sleep(1);
        fun(event_fd);
        goto DONE;
    }

    DONE:
    return 0;
}


