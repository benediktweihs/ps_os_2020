#include <fcntl.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define EAT_DURATION 500
#define NUM_PHILOSOPHER 5
#define EAT_ITERATIONS 1000
#define RIGHT_CHOPSTICK(n) (n)
#define LEFT_CHOPSTICK(n) (((n) + 1) % NUM_PHILOSOPHER)
#define TIME .1

pthread_t philosopher[NUM_PHILOSOPHER];
pthread_mutex_t chopstick[NUM_PHILOSOPHER];

// no the problem does not always occur
// the problem is, that it is possible that several philosophers have only one chopsitck
// assume there are three philosophers. every philosopher having the chopstick to the right of
// him/her is totally possible (every n has executed first command in for loop).. thats already a
// deadlock gets more likely with higher EAT_ITERATIONS.

// as long as ONE chopstick is not taken, no deadlock has occurred.

void* dine(void* id) {
	int n = (int)(intptr_t)id;
	// while(counter != n);  //<-- they must eat sequentially (init. global var. counter)
	for(int i = 0; i < EAT_ITERATIONS; ++i) {
		pthread_mutex_lock(&chopstick[RIGHT_CHOPSTICK(n)]);
		int i = pthread_mutex_trylock(&chopstick[LEFT_CHOPSTICK(n)]);
		if(i) {
			pthread_mutex_unlock(&chopstick[RIGHT_CHOPSTICK(n)]);
			sleep(TIME); // random time to give other threads some time
			continue;
		}
		usleep(EAT_DURATION);
		pthread_mutex_unlock(&chopstick[LEFT_CHOPSTICK(n)]);
		pthread_mutex_unlock(&chopstick[RIGHT_CHOPSTICK(n)]);
	}
	// counter++;  //<-- they must eat sequentially
	printf("Philosopher %d is done eating!\n", n);

	return NULL;
}

int main() {
	// create mutex for every chopstick and do stuff analogous to task 1 and 2
	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_mutex_init(&chopstick[i], NULL);
	}

	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_create(&philosopher[i], NULL, dine, (void*)(intptr_t)i);
	}

	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_join(philosopher[i], NULL);
	}

	for(int i = 0; i < NUM_PHILOSOPHER; ++i) {
		pthread_mutex_destroy(&chopstick[i]);
	}

	return EXIT_SUCCESS;
}
