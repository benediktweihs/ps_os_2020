//
// Created by benedikt on 12.05.20.
//
// --> TimesSecond.pdf (red=task3; black=task3_atomic)


#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/param.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

#define N 1000
#define MAXLEN 256
#define MAXITER 10000

int x;
pthread_mutex_t lock;

void throwExcept(char mes[MAXLEN]) {
    fprintf(stderr, "%s\n", mes);
    exit(EXIT_FAILURE);
}

void* exec(void* args){
	// here we can of course think about whether to lock while the for loop is being executed
	// or only while the value of x will be incremented
	// this way more of the performance is depending on the scheduler
	for(int i = 0; i<MAXITER; i++){
        pthread_mutex_lock(&lock);
        x++;
        pthread_mutex_unlock(&lock);
	}
	return args;
}

int main(void){
	// init mutex
	if(pthread_mutex_init(&lock, NULL)) throwExcept("Mutex creation failed");

	// init threads
    pthread_t ids[N];
	for(int i = 0; i<N; i++) if(pthread_create(ids + i, NULL, exec, (void*) NULL)){
			pthread_mutex_destroy(&lock);
			throwExcept("Thread creation failed");
		}

	// wait for threads to finish and destroy mutex
	for(int i = 0; i<N; i++) if(pthread_join(*(ids + i), NULL)){
			pthread_mutex_destroy(&lock);
			throwExcept("Waiting for threads failed");
		}
	pthread_mutex_destroy(&lock);

	printf("Final value of x: %d\n", x);
	return EXIT_SUCCESS;
}