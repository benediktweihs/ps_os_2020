//
// Created by benedikt on 26.04.20.
//

#include "common.h"

// close shm and fifo
void killSHM(int fd, content* rptr, char* name, FILE* fifo, char* fifoDir) {
	munmap(rptr, sizeof(content));
	shm_unlink(name);
	close(fd);
	fclose(fifo);
	unlink(fifoDir);
	return;
}

// establish shared memory and synchronise communication
int main(int argc, char* argv[]) {
	// check usr input
	if(argc != 2) {
		printf("Try ./task1_a number\n");
		exit(EXIT_FAILURE);
	}
	int nInput = atoi(argv[1]);

	// create space for shared memory
	char name[MAXDIR] = "/sharedcontent";
	int fd = shm_open(name, O_RDWR | O_CREAT, 0777); // TODO Error handling
	int err = ftruncate(fd, sizeof(content));
	if(err) exit(EXIT_FAILURE);
	content* rptr =
	    (content*)mmap(NULL, sizeof(content), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

	// creation of shm is done - now write to shared memory space and open fifo
	rptr->n = nInput;
	char fifoDir[MAXDIR] = "/tmp/sharedContent";
	unlink(fifoDir);
	if(mkfifo(fifoDir, 0777)) {
		printf("Creation of fifo in path %s failed\n", fifoDir);
		exit(EXIT_FAILURE);
	}

	// synchronise programs
	FILE* fifo = fopen(fifoDir, "r");

	// computation done
	uint64_t result;
	int rd = fread(&result, sizeof(uint64_t), 1, fifo);
	if(rd == -1) error("read from fifo");
	killSHM(fd, rptr, name, fifo, fifoDir);

	// done
	printf("Result: %ld\n", result);

	return EXIT_SUCCESS;
}
