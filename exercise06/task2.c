//
// Created by benedikt on 05.05.20.
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

#define N 5
#define MAXLEN 256
#define MAX 10000

// mutex for synchronization - very important that counter gets increased
// only by one thread at a time
// addressing the question: i'd say that semaphores could be used yes
pthread_mutex_t lock;
int counter = 0;

typedef struct passData {
	myqueue* myq;
	int sum;
	int number;
} passData;

void throwExcept(char mes[MAXLEN]) {
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
		while(counter % 6 != threadNumber + 1)
			;
		pthread_mutex_lock(&lock);
		add = myqueue_pop(myq);
		counter++;
		// printf("%d from thread %d\n", add, threadNumber);  // uncomment to see whats going on
		pthread_mutex_unlock(&lock);
		passData1->sum += add;
	} while(add == 1);
	return NULL;
}

int main(void) {
	// initialize pthread_mutex
	if(pthread_mutex_init(&lock, NULL)) throwExcept("mutex init failed");

	// store thread ids
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
		if(pthread_create(ids + i, NULL, &exec, (void*)(data + i)))
			throwExcept("Thread creation failed");
	}
	for(int j = 0; j < MAX / N; j++) {
		while(counter % 6 != 0) {
		}
		pthread_mutex_lock(&lock);
		// critical section of the code
		for(int i = 0; i < N; i++)
			myqueue_push(&globalQ, 1);
		counter++;
		pthread_mutex_unlock(&lock);
	}

	// terminate everything by including zeros
	while(counter % 6 != 0) {
	}
	pthread_mutex_lock(&lock);
	for(int i = 0; i < N; i++)
		myqueue_push(&globalQ, 0); // terminating zeros
	counter++;
	pthread_mutex_unlock(&lock);

	// wait or all threads left to finish
	for(int i = 0; i < N; i++) {
		if(pthread_join(*(ids + i), NULL)) throwExcept("Waiting for thread failed");
	}

	// everything done - now add all results together
	int total = 0;
	for(int i = 0; i < N; i++)
		total += (data + i)->sum;
	printf("All threads combined give a sum of %d\n", total);

	// destroy mutex
	pthread_mutex_destroy(&lock);
	return EXIT_SUCCESS;
}