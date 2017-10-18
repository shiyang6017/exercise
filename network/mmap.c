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
    if (argc != 2) {
        printf("usage: %s filename.\n", argv[0]);
        exit(0);
    }

    int fd = open(argv[1], O_CREAT |O_RDWR, S_IRWXU);

    ftruncate(fd, sizeof share);
   //write(fd, &share, sizeof share);

    if (fd < 0) {
        my_err("open fail");
    }

    struct share_area* shareAreaPtr = mmap(NULL, sizeof share, PROT_WRITE | PROT_READ, MAP_SHARED, fd, 0);
    if (shareAreaPtr == MAP_FAILED) {
        my_err("mmap fail");
    }
    strcpy(shareAreaPtr->head, "Hello world.");
    return 0;
}
