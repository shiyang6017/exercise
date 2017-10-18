//
// Created b_y shiyang on 9/5/17.
//

#include "net.h"

#include <sys/epoll.h>
#include <sys/eventfd.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <memory.h>


void fun(int event_fd) {
    int epoll_fd = epoll_create1(EPOLL_CLOEXEC); // EPOLL_NONBLOCK

    if (epoll_fd < 0) {
        print_err("epoll_crearte1 err.");
    }

    struct epoll_event *event = (struct epoll_event *) (malloc(sizeof(struct epoll_event)));
    memset(event, 0, sizeof *event);
    event->events = EPOLLIN;
    event->data.fd = event_fd;

    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, event_fd, event) < 0) {
        print_err("epoll_ctl err");
    }

    const int SIZE = 1024;
    struct epoll_event ready_events[SIZE];
    int ready_nums;

    while (1) {
        if ((ready_nums = epoll_wait(epoll_fd, ready_events, SIZE, -1)) < 0) {
            print_err("epoll_wait err");
        }

        printf("ready_nums = %d\n", ready_nums);

        for (int i = 0; i < ready_nums; ++i) {
            int fd = ready_events[i].data.fd;
            printf("the ready fd is %d, %d\n", fd, event_fd);
            if (fd == event_fd) {
                uint64_t val;
                if (read(fd, &val, sizeof val) != sizeof val) {
                    print_err("read err 2");
                }
                printf("the value of val = %d\n", val);
            }
        }
    }
}


void main() {

    int event_fd = eventfd(0, EFD_NONBLOCK);
    if (event_fd < 0) {
        print_err("eventfd err");
    }

    uint64_t val;
    pid_t child_pid;

    if ((child_pid = fork()) == 0) {
        uint64_t val = 123;
        if (write(event_fd, &val, sizeof val) != sizeof val) {
            print_err("write err");
        }
        exit(0);
    } else if (child_pid > 0) {
        fun(event_fd);
        exit(0);
    } else {
        print_err("fork err");
    }

    return 0;
}