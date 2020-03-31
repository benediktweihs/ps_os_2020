#include <signal.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> // fork
#include <sys/wait.h>  // wait
#include <unistd.h>    // sleep, getpid

int pid;
volatile bool childTerm = false;
bool parentSentFirst = false;
bool blockSigUsr2 = true;

// create handle function for child and parent
void create_listener(struct sigaction* act, void func(int)) {
	memset(act, 0, sizeof(struct sigaction));
	act->sa_handler = func;
	sigaction(SIGUSR1, act, NULL);
	sigaction(SIGUSR2, act, NULL);
	sigaction(SIGALRM, act, NULL);
}

void handler_parent(int sig) {
	if(sig == SIGUSR1) { // only if child is done
		childTerm = true;
		printf("Parent done\n");
	}

	if(sig == SIGALRM) {
		if(parentSentFirst && !childTerm) {
			kill(pid, SIGUSR1);
		} else {
			kill(pid, SIGUSR1);
			kill(pid, SIGUSR2);
			parentSentFirst = true;
		}
		alarm(3);
	}
}

void handler_child(int sig) {
	if(sig == SIGUSR2) { // unblocks SIGUSR2
		blockSigUsr2 = false;
	}
	if(sig == SIGUSR1) { // happens every 3 seconds;
		printf("Received SIGUSR1\n");
	}
	if(sig == SIGALRM && !blockSigUsr2) { // happens after 13 sec.
		kill(getppid(), SIGUSR1);
		printf("Child done\n");
	}
}

int main(void) {
	alarm(3);
	struct sigaction act_parent, act_child;
	create_listener(&act_parent, handler_parent);

	// create listener child and making sure in 13 sec. sigusr2 is no longer ignored
	pid = fork();
	if(pid == 0) {
		alarm(13);
		create_listener(&act_child, handler_child);
		while(!childTerm)
			;
		return 0;
	}

	while(!childTerm)
		; // wait for child and
	return EXIT_SUCCESS;
}