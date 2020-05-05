//
// Created by benedikt on 26.04.20.
//

#include "common.h"

void killSHM(int fd, content* rptr, char* name, FILE* fifo, char* fifoDir) {
	munmap(rptr, sizeof(content));
	shm_unlink(name);
	close(fd);
	fclose(fifo);
	unlink(fifoDir);
	return;
}

int main(void) {
	// get data from shared memory space
	char name[MAXDIR] = "/sharedcontent";
	int fd = shm_open(name, O_RDWR, 0666);
	content* rptr =
	    (content*)mmap(NULL, sizeof(content), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(rptr == MAP_FAILED) printf("mmap failed\n");
	uint64_t N = rptr->n;

	// measure time
	clock_t time0, time1;

	// producer - consumer pattern
	// first child aka producer
	pid_t pidProd = fork();
	if(pidProd == 0) {
		for(uint64_t i = 0; i <= N; i++) {
			*(rptr->buffer + i % N) = i;
		}
		exit(EXIT_SUCCESS);
	}

	// second child aka consumer
	pid_t pidCons = fork();
	if(pidCons == 0) {
		// compute sum of elements in ring buffer and store in shared memory
		uint64_t sum = 0;
		time0 = clock();
		for(uint64_t i = 0; i <= N; i++) {
			sum += *(rptr->buffer + i % N);
		}
		time1 = clock();
		double time_taken = (double)(time1 - time0) / (double)(CLOCKS_PER_SEC);
		printf("%f\n", 1000 * time_taken);
		rptr->n = sum;
		exit(EXIT_SUCCESS);
	}

	// parent waits
	wait(NULL);

	// here producer consumer are done
	// synchronise programs, cleanup and write result to fifo
	char fifoDir[MAXDIR] = "/tmp/sharedContent";
	FILE* fifo = fopen(fifoDir, "w");
	uint64_t result = rptr->n;
	fwrite(&result, sizeof(uint64_t), 1, fifo);
	killSHM(fd, rptr, name, fifo, fifoDir);

	return EXIT_SUCCESS;
}
