//
// Created b_y shiyang on 9/5/17.
//


#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/mman.h>
#include <unistd.h>
#include <memory.h>
#include <sys/wait.h>
#include <errno.h>

void my_err(const char *msg) {
    perror(msg);
    exit(0);
}

#define SHARE_AREA_INITIALIZER {{0}, 0, PTHREAD_MUTEX_INITIALIZER}

struct share_area {
    char head[1024];
    int val;
    pthread_mutex_t mutex;
};

struct share_area share = SHARE_AREA_INITIALIZER;

int main(int argc, char* argv[]) {

    int fd = open("/dev/zero", O_CREAT |O_RDWR, S_IRWXU);

    if (fd < 0) {
        my_err("open fail");
    }

  //  struct share_area* shareAreaPtr = mmap(NULL, sizeof share, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    struct share_area* shareAreaPtr = mmap(NULL, sizeof share, PROT_WRITE | PROT_READ, MAP_SHARED | MAP_ANON, -1, 0);
    if (shareAreaPtr == MAP_FAILED) {
        my_err("mmap fail");
    }



    int chld_pid;
    if ((chld_pid = fork()) == 0) {
        strcpy(shareAreaPtr->head, "Hello world.");
        exit(0);
    } else if (chld_pid < 0) {
        my_err("fork err");
    }

    while (wait(NULL) < 0) {
        if (errno ==  EAGAIN) {
            continue;
        } else {
            my_err("wait err");
        }
    }
    printf("%s", shareAreaPtr->head);
    return 0;
}
