#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>

/*
 * comments: order of prints is not always the same
 * it depends on how much processing time each child gets.
 * it can not be predicted.
 */

unsigned fib(unsigned);

int main(int argc, char* argv[]){

    // make sure the input paramters are right
    if(argc!=2){
        printf("One input parameter needed.\n");
        return EXIT_FAILURE;
    }
    int N = atoi(argv[1]);
    if(N <= 0) return EXIT_FAILURE;

    // create N child porcesses
    for(int i = 0; i<N; i++){
        if(fork()==0){
            printf("Child %d PID = %d. Fib(40) = %u\n", i, getpid(), fib(40));
			return EXIT_SUCCESS;
        }
    }

    // Wait for child processes
    for(int i = 0; i<N; i++) wait(NULL);

	return EXIT_SUCCESS;
}

unsigned fib(unsigned n) {
    if(n <= 1) return n;
    return fib(n - 1) + fib(n - 2);
}
