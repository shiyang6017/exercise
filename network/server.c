//
// Created b_y shiyang on 9/4/17.
//


#include "net.h"


char buf[128];


void fun(int fd) {
  //SY    read(fd, buf, sizeof buf);
}

void server(const char *ip_addr, uint16_t port) {
    int listen_fd = tcp_socket();
    enable_so_reuseaddr(listen_fd);
    tcp_bind(listen_fd,port, ip_addr);

    if (listen(listen_fd, 128) < 0 ) {
        print_err("listen err");
    }

    while (true) {
        int client_fd = accept(listen_fd, NULL, NULL);
        if (client_fd < 0) {
            print_err("accept failed");
        }
        ssize_t size; 
        while ((size = read(client_fd, buf, sizeof buf)) > 0 );
        if (size < 0) {
            print_err("read err");
        }
        close(client_fd);

        printf("%s\n", buf);
       // close(client_fd); 
        fun(client_fd);
        
        printf("close client_fd\n");
    }
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("usage: %s ip_addr [ip_port]", argv[0]);
        exit(0);
    }

    uint16_t port = 8080;

    if (argc == 3) {
        port = (uint16_t) atoi(argv[2]);
        printf("server port : %d\n", port);
    }

    server(argv[1], port);

    return 0;
}