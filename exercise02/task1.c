// Written by David Bänsch, Benedikt Weihs, Thomas Tappeiner as all tasks in
// this folder were

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // fork
#include <sys/wait.h>  // wait
#include <unistd.h>    // sleep, getpid

// maaaan i like git

unsigned fib(unsigned n) {
	if(n <= 1) return n;
	return fib(n - 1) + fib(n - 2);
}

void child( int child_number )
{
    const unsigned fib_result = fib( 40 );
    printf( "Child %2i PID = %5i. Fib(40) = %u\n",
            child_number,
            getpid(),
            fib_result );
}

int
main( int argc, char * argv[] )
{
    if( argc != 2 )
    {
        printf( "Usage: %s number_of_children\n", argv[ 0 ] );
        return 1;
    }

    for( int i = 0; i < atoi( argv[ 1 ] ); i++ )
    {
        int pid_res = fork();

        if( !pid_res )
        {
            child( i + 1 );
            return 0;
        }
    }

    for( int i = 0; i < ( *argv )[ 1 ]; i++ )
        wait( NULL );
    return 0;
}

