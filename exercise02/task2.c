#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

#define TIME 5

bool resume = false;

// when child sends signal to parent:
void handler(){
    resume = true;
}

int main(void){
    struct sigaction act;
    memset( &act, '\0', sizeof( struct sigaction ) );
    act.sa_handler = handler;

    if(fork()==0){
        printf("Child %d sleeping for 5 secondqs...\n", getpid());
        sleep(TIME);
        printf("Child done\n");
        kill( getppid(), SIGUSR1 ); // send signal to parent
		return EXIT_SUCCESS;
    }

    while(!resume) sigaction( SIGUSR1, &act, NULL ); // resume only if child is done
    printf("Parent done\n");
    return EXIT_SUCCESS;
}