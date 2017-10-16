//
// Created by shiyang on 9/4/17.
//

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
void main() {
    int fd = open("eof.txt", O_RDWR | O_CREAT, S_IRWXU);
    char buf[1024];
    int len = read(fd, buf, 1024);
    printf("%d\n", len);
    return 0;
}
