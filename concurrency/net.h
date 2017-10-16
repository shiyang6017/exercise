//
// Created by shiyang on 9/10/17.
//

#ifndef EXERCISE_NET_H
#define EXERCISE_NET_H

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <wait.h>
#include <stdbool.h>

#define unlikely(x) __builtin_expect(!!(x), 0)
#define likely(x) __builtin_expect(!!(x), 1)

#define print_err(msg) do {perror(msg); exit(0); } while (0)
#define print_exit(msg) do {printf(msg); exit(0); } while (0)

int tcp_socket();

struct sockaddr_in *tcp_sockaddr_in(uint16_t port, const char *str_ip_addr);

struct sockaddr_in *tcp_bind(int listen_fd, uint16_t port, const char *str_ip_addr);

struct sockaddr_in *tcp_bind2(int listen_fd, uint16_t port);

int tcp_connect(int fd, struct sockaddr_in *);

void enable_so_reuseaddr(int fd);
#endif //EXERCISE_NET_Hls

