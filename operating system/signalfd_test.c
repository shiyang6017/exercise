//
// Created by shiyang on 9/18/17.
//
#include <stdio.h>
#include <sys/signalfd.h>
#include "net.h"

void main() {
    sigset_t mask;
    int sigfd;
    struct signalfd_siginfo ssinfo;

    sigemptyset(&mask);
    sigaddset(&mask, SIGINT);
    if (sigprocmask(SIG_BLOCK, &mask, NULL) < 0) print_err("sigprocmask err");
    if ((sigfd = signalfd(-1, &mask, 0)) < 0) print_err("signalfd err");

    while (1) {
        ssize_t len = read(sigfd, &ssinfo, sizeof(ssinfo));
        if (len < 0) print_err("read err");
        if (ssinfo.ssi_signo == SIGINT) {
            printf("get SIGINT, err = %d\n", ssinfo.ssi_errno);
        }
    }

    return 0;
}