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
	if(fd == -1) error("shm_open failed\n");
	content* rptr =
	    (content*)mmap(NULL, sizeof(content), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(rptr == MAP_FAILED) error("mmap failed\n");
	uint64_t N = rptr->n;

	// create semaphores
	sem_t* semProd;
	if((semProd = sem_open(SEMPROD, O_RDWR | O_CREAT, 0777, BUFSIZE)) == SEM_FAILED)
		error("shm_open failed");
	sem_t* semCons;
	if((semCons = sem_open(SEMCONS, O_RDWR | O_CREAT, 0777, 0)) == SEM_FAILED)
		error("shm_open failed");

	// measure time
	clock_t time0, time1;

	// producer - consumer pattern - note that synchroinsing by using the shm would work as well
	// first child aka producer
	pid_t pidProd = fork();
	if(pidProd == 0) {
		// write iteratively to buffer
		// semaphore will block until consumer has consumed enough
		for(uint64_t i = 0; i <= N; i++) {
			sem_wait(semProd);
			*(rptr->buffer + i % N) = i;
			sem_post(semCons);
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
			sem_wait(semCons);
			sum += *(rptr->buffer + i % N);
			sem_post(semProd);
		}
		time1 = clock();
		double time_taken = (double)(time1 - time0) / (double)(CLOCKS_PER_SEC);
		printf("%f\n", 1000 * time_taken);
		rptr->n = sum;
		exit(EXIT_SUCCESS);
	}

	// close semaphores
	if(sem_close(semCons)) error("close_semaphore");
	if(sem_close(semProd)) error("close_semaphore");
	if(sem_unlink(SEMCONS)) error("unlink_semaphore");
	if(sem_unlink(SEMPROD)) error("unlink_semaphore");

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
