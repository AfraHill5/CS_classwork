#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS 8

void task(void* arg) {
    int tid;
    tid = *((int*)  arg);
    printf("Hello world from thread #%d.\n", tid);

    return NULL;
}


int main() {
    pthread_t threads[NUM_THREADS];
    int threadArgs[NUM_THREADS];
    int rc, i;

    /* create the threads */
    for (i = 0; i < NUM_THREADS; i++) {
        threadArgs[i] = i; 
        printf("MAIN: creating thread #%d.\n", i);
        rc = pthread_create(&threads[i], NULL, task, 
                (void*) &threadArgs[i]);       
    }

    /* now wait for all threads to complete */
    for (i = 0; i < NUM_THREADS; i++) {
        rc = pthread_join(threads[i], NULL);
    }

    exit(EXIT_SUCCESS);
}

