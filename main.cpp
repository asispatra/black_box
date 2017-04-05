#include <pthread.h>
#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <string>
#include <cstring>
#include <sstream>

#include "thread.h"
#include "network.h"

#define MAXDATASIZE 100

using namespace std;

/* 
 * This is a starting port number. 
 * This will help to assign each neuron an uniq port number. 
 */
static int seq = 3490;

/*
 * A neuron defination. 
 * Neuron behaviour can be different based on implementation.
 * Based on neuron behaviour Neuron can be different types.
 */
class Neuron {
private:
    string key;     /* Key */
    string value;   /* Value or Reply or Answer */
    string port;    /* Server communication port */
    vector<string> client_ports;    /* List of ports to connected neurons */

    /* Wrapper of behaviour_handler to overcome fn_ptr to C function */
    static void wrapper_bh(int fd, void *future) {
        Neuron *obj = (Neuron *)future;
        obj->behaviour_handler(fd);
    }
    /* Wrapper of service_server_network to overcome fn_ptr to C function */
    static void *wrapper_ssn(void *dummy) {
        Neuron *obj = (Neuron *)dummy;
        obj->service_server_network();
    }

    /* Define neuron behaviour */
    void behaviour_handler(int fd) {
        char buf[MAXDATASIZE];
        int num = rx(fd, buf, MAXDATASIZE);
        printf("Server received from Client: ### %s :: %d\n", buf, num);
    } 
    /* Create neuron port for incoming communication */
    void service_server_network() {
        create_server(port.c_str(), wrapper_bh, this);
        pthread_exit(NULL);
    }
public:
    /* Neuron constructor with key and value */
    Neuron(string key, string value) {
        stringstream convert;
        convert << seq;
        port = convert.str();
        create_thread(wrapper_ssn, this); 
    }
};

/* 
 * These are two functions to test the Neuron
 */
void tx_handeler(int fd, void *future) {
    tx(fd, "Hello World!");
}

void *service_client_network(void *dummy) {
    create_client("127.0.0.1", "3490", tx_handeler, NULL);
    pthread_exit(NULL);
}

int main() {
    Neuron n("name", "Steve");

    /* Test purpose */
    sleep(2);
    create_thread(service_client_network, NULL);
    sleep(2);
    create_thread(service_client_network, NULL);
    pthread_exit(NULL);
}
