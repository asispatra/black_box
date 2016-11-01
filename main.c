#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "network.h"

#define MAXDATASIZE 100

void tx_handeler(int fd) {
    tx(fd, "Hello World!!!!!");
}

void *service_server_network(void *dummy) {
    create_server("3490", tx_handeler);
    pthread_exit(NULL);
}

void rx_handeler(int fd) {
    char buf[MAXDATASIZE];
    int num = rx(fd, buf);
    printf("### %s :: %d\n", buf, num);
}

void *service_client_network(void *dummy) {
    create_client("localhost", "3490", rx_handeler);
    pthread_exit(NULL);
}

int main() {
    create_thread(service_server_network);
    sleep(3);
    create_thread(service_client_network);
    sleep(3);
    create_thread(service_client_network);
    sleep(3);
    create_thread(service_client_network);
    pthread_exit(NULL);
}

