#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include "thread.h"

void create_thread(thread_fn_t fun_ptr, void *future) {
    pthread_t thread;
    int rc;
    rc = pthread_create(&thread, NULL, fun_ptr, future);
    if (rc){
        fprintf(stderr, "ERROR; return code from pthread_create() is %d\n", rc);
        exit(-1);
    }
}

