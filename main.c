#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread.h"
#include "network.h"

void (*handler)(int fd) = NULL;

#define MAXDATASIZE 100

void tx_handeler(int fd) {
    tx(fd, "Hello World!");
}

void behaviour_handler(int fd) {
    /*
    Purpose: A behaviour_fn of neuron named "NAME"
    */

    char buf[MAXDATASIZE];
    int num = rx(fd, buf, MAXDATASIZE);
    printf("Server received from Client: ### %s :: %d\n", buf, num);
}

void *service_client_network(void *dummy) {
    /*
    Purpose: Create a network service as a client
    */

    //create_client("9.41.164.238", "3490", tx_handeler);
    //create_client("localhost", "3490", tx_handeler); // Getting warning ==> client: connect: Connection refused
    create_client("127.0.0.1", "3490", tx_handeler);
    pthread_exit(NULL);
}

void *service_server_network(void *dummy) {
    /*
    Purpose: Create a network service as a server
    */

    void (*handler_local)(int fd) = handler;
    handler = NULL;
    create_server("3490", handler_local);
    pthread_exit(NULL);
}

void create_neuron(char *name, void (*arg_behaviour_handler)(int fd)) {
    /*
    Purpose: Create a neuron on demand with a name and behaviour function. 
    Arguments:
        name: A name to identify the neuron uniquely.
        behaviour_fn: A function or handler which describe the behaviour of the neuron.
    Returns: None

    neuron: On demand creation.
    One server port - receive inputs
    Multiple Client port - send output - On demand creation.
    Give an unique name to identify
    */

    handler = arg_behaviour_handler;
    create_thread(service_server_network);
}

int main() {
    create_neuron("NAME", behaviour_handler);
    sleep(3);
    create_thread(service_client_network);
    sleep(2);
    create_thread(service_client_network);
    pthread_exit(NULL);
}

