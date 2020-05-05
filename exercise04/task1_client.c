//
// Created by benedikt on 21.04.20.
//
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

int main(int argc, char* argv[]) {
	// make sure there are a correct number of inputs
	if(argc != 2) {
		printf("try ./task1_server client");
		exit(EXIT_FAILURE);
	}

	char fifoDir[MAXBUF] = "/tmp/";
	char fifoName[MAXBUF];
	strcpy(fifoName, fifoDir);
	strcat(fifoName, argv[1]);
	char mes[MAXBUF];

	// communicate with usr
	mkfifo(fifoName, 0777);
	bool isFirstIteration = true;
	int fd;

	// write message in fifo
	while(true) {
		printf("> ");
		if(isFirstIteration) fd = open(fifoName, O_WRONLY);
		if(!fgets(mes, MAXBUF, stdin) || strlen(mes) <= 1) mes[0] = '\0';
		if(!isFirstIteration) fd = open(fifoName, O_WRONLY);
		write(fd, mes, MAXBUF + 1);
		close(fd);
		if(mes[0] == '\0') break;
		isFirstIteration = false;
	}
	return EXIT_SUCCESS;
}
