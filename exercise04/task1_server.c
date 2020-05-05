#define _GNU_SOURCE
#define MAXBUF 100
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <unistd.h>

// in the future: use poisx standard!

int main(int argc, char* argv[]) {
	// make sure there are a correct number of inputs
	if(argc < 2) {
		printf("try ./task1_server client1 client2 ...");
		exit(EXIT_FAILURE);
	}

	// make directory for fifo
	int numberClients = argc - 1;
	int fd[numberClients];
	char* fifoDir = "/tmp/";

	// name fifos
	char fifoNames[numberClients][MAXBUF];
	char mes[MAXBUF];

	// make fifos
	for(int i = 0; i < numberClients; i++) {
		strcpy(fifoNames[i], fifoDir);
		strcat(fifoNames[i], argv[i + 1]);
		mkfifo(fifoNames[i], 0777);
	}

	printf("Server is online\n\n");

	// read connected Fifos
	int closedFifos = 0;
	bool isFirstIteration = true;

	while(true) {
		// all clients are disconnected
		if(closedFifos == numberClients) break;
		for(int i = 0; i < numberClients; i++) {
			fd[i] = open(fifoNames[i], O_RDONLY);
			if(fd[i] == -1 && !isFirstIteration) continue;
			if(isFirstIteration) printf("%s connected\n", argv[i + 1]);
			isFirstIteration = false;
			read(fd[i], mes, MAXBUF);
			if(mes[0] == '\0') {
				close(fd[i]);
				closedFifos++;
				fd[i] = -1;
				printf("%s disconnected\n", argv[i + 1]);
				continue;
			}
			printf("User %s says: %s\n", argv[i + 1], mes);
			close(fd[i]);
		}
	}

	// terminate
	for(int i = 0; i < numberClients; i++) {
		close(fd[i]);
	}
	return EXIT_SUCCESS;
}
