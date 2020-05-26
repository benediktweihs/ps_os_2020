//
// Created by benedikt on 12.05.20.
//
#include "myqueue.h"
#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N 50
#define MAXLEN 256
#define MAX 10000

pthread_spinlock_t lock;
int counter;

typedef struct passData {
	int sum;
	int number;
	myqueue* myq;
} passData;

void throwExcept(char mes[MAXLEN]){
    fprintf(stderr, "%s\n", mes);
    exit(EXIT_FAILURE);
}

void* exec(void* args) {
    int add;
    passData* passData1 = (passData*)args;
    myqueue* myq = passData1->myq;
    int threadNumber = passData1->number;
    do {
        // critical section of the code - use mutex to synchronize threads
        while(counter % (N + 1) != threadNumber + 1);
        pthread_spin_lock(&lock);
        add = myqueue_pop(myq);
        counter++;
        printf("%d from thread %d\n", add, threadNumber);  // uncomment to see whats going on
        pthread_spin_unlock(&lock);
        passData1->sum += add;
    } while(add == 1);
    return NULL;
}


int main(void) {
	// initialize pthread_mutex
	if(pthread_spin_init(&lock, PTHREAD_PROCESS_SHARED)){
        pthread_spin_destroy(&lock);
		throwExcept("spin init failed");
	}

	// store thread ids and queue
	pthread_t ids[N];
	passData data[N];
	myqueue globalQ;
	myqueue_init(&globalQ);
	for(int i = 0; i < N; i++) {
		(data + i)->sum = 0;
		(data + i)->number = i;
		(data + i)->myq = &globalQ;
	}

	// thread creation
	for(int i = 0; i < N; i++) {
		if(pthread_create(ids + i, NULL, &exec, (void*)(data + i))) {
			pthread_spin_destroy(&lock);
			throwExcept("Thread creation failed");
		}

		}
	for(int j = 0; j < MAX / N; j++) {
        while(counter % (N+1) != 0){}
		pthread_spin_lock(&lock);
		// critical section of the code
		for(int i = 0; i < N; i++) myqueue_push(&globalQ, 1);
		counter++;
		pthread_spin_unlock(&lock);
	}

	// terminate everything by including zeros
    while(counter % (N+1) != 0){}
	pthread_spin_lock(&lock);
	for(int i = 0; i < N; i++) myqueue_push(&globalQ, 0); // terminating zeros
	counter++;
	pthread_spin_unlock(&lock);

	// wait or all threads left to finish
	for(int i = 0; i < N; i++) {
		if(pthread_join(*(ids + i), NULL)) {
		    pthread_spin_destroy(&lock);
		    throwExcept("Waiting for thread failed");
	    }
	}

	// everything done - now add all results together
	int total = 0;
	for(int i = 0; i < N; i++) total += (data + i)->sum;
	printf("All threads combined give a sum of %d\n", total);

	// destroy mutex
	pthread_spin_destroy(&lock);
	return EXIT_SUCCESS;
}