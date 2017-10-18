//
// Created b_y shiyang on 9/4/17.
//

#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <setjmp.h>
#include <stdlib.h>

typedef void (*Handler)(int);

void my_err(const char *msg) {
    perror(msg);
    exit(0);
}

jmp_buf jmpBuf;

void signal_process(int signal) {
    switch (signal) {
        case SIGALRM:
            printf("receive SIGALRM.\n");
            break;
        default:
            fprintf(stderr, "something goes wrong : receive %d\n", signal);
    }
    longjmp(jmpBuf, 1);
}

Handler Signal(int sig, Handler handler) {
    struct sigaction oldSig, newSig;

    newSig.sa_handler = handler;

    sigemptyset(&(newSig.sa_mask));
    newSig.sa_flags = 0;

    if (sig == SIGALRM) {
#ifdef SA_INTERRUPT
        newSig.sa_flags |= SA_INTERRUPT;
#endif
    } else {
        newSig.sa_flags |= SA_RESTART;
    }

    if (sigaction(sig, &newSig, &oldSig) < 0)
        return (SIG_ERR);
    else
        return (oldSig.sa_handler);
}

int my_sleep(int seconds) {

    if (Signal(SIGALRM, signal_process) == SIG_ERR) {
        my_err("Signal err");
    }
    if (setjmp(jmpBuf) == 0) {
        alarm(seconds);
        pause();
    } else {
        return alarm(0);
    }
}

void main() {
    my_sleep(4);
    return 0;
}
