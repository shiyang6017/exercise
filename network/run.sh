#!/bin/bash

kill -9 $(pidof server)
kill -9 $(pidof client)

gcc -g -o server server.c net.c
gcc -g -o client nonblock_connect.c net.c
echo "start server"
#./server 127.0.0.1 8082 &
echo "end server"

sleep 1
echo "start client"
./client 127.0.0.1 8082 127.0.0.1 1235 &
echo "end client"
