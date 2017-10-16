//
// Created by shiyang on 9/4/17.
//
#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <setjmp.h>
#include <stdlib.h>

void my_err(const char *msg) {
    perror(msg);
    exit(0);
}

int val = 0;

jmp_buf jmpBuf;


void handler(int sig) {}

void main() {

    sigset_t sigSet;
    sigemptyset(&sigSet);
    sigaddset(&sigSet, SIGALRM);

    sigset_t oldSigSet;

    if (signal(SIGALRM, handler) == SIG_ERR) {
        my_err("signal err");
    }

    if (sigprocmask(SIG_SETMASK, &sigSet, &oldSigSet) < 0) {
        my_err("sigprocmask err");
    }

    int child_pid;
    printf("val = %d\n", val);
    if ((child_pid = fork()) == 0) {
        kill(getppid(), SIGALRM);
        return 0;
    }

    sigset_t maskSet;
    sigemptyset(&maskSet);

    if (sigsuspend(&maskSet) != -1 ) {
        my_err("sigsuspend err");
    }

    if (sigprocmask(SIG_SETMASK, &oldSigSet, NULL) < 0) {
        my_err("sigprocmask err");
    }

    return 0;
}