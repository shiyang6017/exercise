//
// Created b_y shiyang on 9/18/17.
//

//
// Created b_y shiyang on 9/18/17.

#include <sys/eventfd.h>
#include <sys/epoll.h>
#include <sys/timerfd.h>
#include "net.h"


// totally ignore return-value check



void main() {
    int timer_fd = timerfd_create(CLOCK_MONOTONIC, 0);
/*
    struct timespec begin_time;
    struct timespec time_interval = {1, 0};
    if (clock_gettime(CLOCK_MONOTONIC, &begin_time) < 0) {
        print_err("clock_gettime error");
    }
*/
    struct itimerspec timer = {{0, 0}, {1, 0}};

    // if
    if (timerfd_settime(timer_fd, 0, &timer, NULL) < 0) {
        print_err("timerfd_settime error");
    }
    while (1) {
        static uint64_t time_out_count = 0;
        if (read(timer_fd, &time_out_count, sizeof time_out_count) < 0) {
            print_err("read error");
        } else {
            printf("time_out_count:= %lu\n", time_out_count);
        }
    }
    return 0;
}


