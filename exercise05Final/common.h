//
// Created by benedikt on 26.04.20.
//

#include <fcntl.h>
#include <semaphore.h>
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
#ifndef H_GUARD
#define H_GUARD

#define MAXDIR 256
#define BUFSIZE 10
#define SEMPROD "/synchCirkArrPr"
#define SEMCONS "/synchCirkArrCr"

// struct is stored in shared memory
typedef struct content {
	uint64_t n;
	uint64_t buffer[BUFSIZE];
} content;

// Print system error and exit
void error(char* msg) {
	perror(msg);
	exit(EXIT_FAILURE);
}

#endif
