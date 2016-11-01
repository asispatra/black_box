#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

void create_thread(void *(*fun_ptr)(void *dummy)) {
    pthread_t thread;
    int rc;
    rc = pthread_create(&thread, NULL, fun_ptr, NULL);
    if (rc){
        fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
}

