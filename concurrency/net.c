//
// Created by shiyang on 9/10/17.
//
#include <memory.h>
#include "net.h"

int tcp_socket() {
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd < 0) {
        print_err("socket failed.");
    }
    return sock_fd;
}

struct sockaddr_in* tcp_sockaddr_in(uint16_t port, const char *str_ip_addr) {
    struct sockaddr_in *sockaddr_in = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));

    if (sockaddr_in == NULL) {
        perror("malloc err");
    }

    bzero(sockaddr_in, sizeof(struct sockaddr_in));
    if (str_ip_addr != NULL) {
        int err = inet_pton(AF_INET, str_ip_addr, &(sockaddr_in->sin_addr));
        switch (err) {
            case 0:
                print_exit("the format of ip_addr is err.");
                return NULL;
                break;
            case -1:
                print_err("inet_pton failed.");
                break;
            default:
                break;
        }
    } else {
        sockaddr_in->sin_addr.s_addr = INADDR_ANY;
    }
    sockaddr_in->sin_port = htons(port);
    sockaddr_in->sin_family = AF_INET;

    return sockaddr_in;
}

struct sockaddr_in *tcp_bind(int listen_fd, uint16_t port, const char *str_ip_addr) {

    struct sockaddr_in *sockaddr_in = tcp_sockaddr_in(port, str_ip_addr);

    int err = bind(listen_fd, (struct sockaddr *) sockaddr_in, sizeof(struct sockaddr_in));
    if (err != 0) {
        print_err("bind failed.");
    }

    return sockaddr_in;
}

struct sockaddr_in *tcp_bind2(int listen_fd, uint16_t port) {
    struct sockaddr_in *sockaddr_in =  tcp_sockaddr_in(port, NULL);

    int err = bind(listen_fd, (struct sockaddr *) sockaddr_in, sizeof(struct sockaddr_in));

    if (err != 0) {
        print_err("bind failed.");
    }

    return sockaddr_in;
}

void enable_so_reuseaddr(int fd) {
    int optval = 1;
    if (setsockopt(fd, SOL_SOCKET,SO_REUSEADDR, (void*)&optval, sizeof optval) != 0) {
        print_err("setsockopt err");
    }
}
