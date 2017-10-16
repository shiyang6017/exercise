//
// Created by shiyang on 9/5/17.
//

#include <memory.h>
#include <fcntl.h>
#include "net.h"

char buf[] = "HELLO WORLD";

void client(const char* server_ip_addr, uint16_t server_port, const char* client_ip_addr, uint16_t client_port) {

    int fd = tcp_socket();
  // enable_so_reuseaddr(fd);
    if (client_port != 0 && client_ip_addr != NULL) {
       // tcp_bind(fd, client_port, client_ip_addr);
    }

    int flag; 
    if ( (flag = fcntl(fd, F_GETFL, 0)) < 0) {
        print_err("fcntl err");
    }
    
    flag |= O_NONBLOCK; 

    if (fcntl(fd, F_SETFL, flag) < 0) {
        print_err("fcntl err"); 
    }

    struct sockaddr_in* sockaddr_in = tcp_sockaddr_in(server_port, server_ip_addr);

    if (connect(fd,(struct sockaddr*) sockaddr_in, sizeof (*sockaddr_in)) != 0) {
        if (errno != EINPROGRESS) {
            print_err("connect err");
        }
    }
    int err;
    socklen_t err_len;
    if (getsockopt(fd, SOL_SOCKET, SO_ERROR, &err, &err_len) != 0) {
        print_err("setsockopt err.");
    }
    
    if (err != 0) {
        print_err("connect fail");
    }

    if (send(fd, buf, sizeof buf + 1, 0) < 0) {
        printf("send err \n");
    }
}

int main(int argc, char *argv[]) {

    if (argc < 3) {
        printf("usage : %s server_ip server_port [client_ip client_port ]\n", argv[0]);
        exit(0);
    }

    uint16_t server_port = atol(argv[2]);
    const char* client_ip_addr = NULL;
    uint16_t client_port = 0;

        client_port = atol(argv[4]);
        client_ip_addr = argv[3];

    client(argv[1], server_port, client_ip_addr, client_port);
    return 0;
}