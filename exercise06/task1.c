//
// Created by benedikt on 05.05.20.
//
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

#define N 10
#define MAXLEN 256

typedef struct passData {
	int number;
	bool isCancelled;
} passData;

// better use errno - will do next time
void throwExcept(char mes[MAXLEN]) {
	fprintf(stderr, "%s\n", mes);
	exit(EXIT_FAILURE);
}

void* exec(void* args) {
	// if the program must be very robust add another flag
	// to check if main has already decided to cancel thread or not
	passData* data = (passData*)args;
	int threadNumber = data->number;

	// create threadN.txt String
	char str[MAXLEN];
	sprintf(str, "thread%d.txt", threadNumber);

	// create File
	FILE* fp;
	fp = fopen(str, "w");
	fclose(fp);

	// best solution I can come up with. maybe there is a better solution by using pthread_cancel
	// I cant find a function from the lib pthread.h which has the functionality to cancel a thread
	// after it executed a given set of commands
	struct timespec start, end;
	double timeTaken = 0;
	clock_gettime(CLOCK_MONOTONIC, &start);
	while(!data->isCancelled && timeTaken < 2) {
		clock_gettime(CLOCK_MONOTONIC, &end);
		timeTaken = (end.tv_sec - start.tv_sec);
	}

	// if thread got cancelled then timeTaken is not necessarily greater than 2 and thread deletes
	// file
	if(data->isCancelled) remove(str);
	return NULL;
}

int main(void) {
	// initialize random generator
	srand(time(NULL));

	// store thread ids
	pthread_t ids[N];
	passData data[N];
	for(int i = 0; i < N; i++) {
		(data + i)->number = i;
		(data + i)->isCancelled = false;
	}

	// thread creation
	for(int i = 0; i < N; i++) {
		if(pthread_create(ids + i, NULL, &exec, (void*)(data + i)))
			throwExcept("Thread creation failed");
	}

	// wait a second and then start canceling threads
	sleep(1);

	for(int i = 0; i < N; i++) {
		if(rand() % 2) {
			(data + i)->isCancelled = true;
			printf("Thread %d cancelled\n", i);
		} else
			printf("Thread %d not cancelled\n", i);
	}

	// wait or all threads left to finish
	for(int i = 0; i < N; i++) {
		if(pthread_join(*(ids + i), NULL)) throwExcept("Waiting for thread faileds");
	}

	return EXIT_SUCCESS;
}