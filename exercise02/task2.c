#define _POSIX_SOURCE
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // fork
#include <unistd.h>    // sleep, getpid
#include <sys/wait.h>  // wait
#include <signal.h>

int no_sig = 1;

void
child()
{
    printf( "Child %5i sleeping for 5 seconds...\n", getpid() );
    sleep( 5 );
    printf( "Child done\n" );
    kill( getppid(), SIGUSR1 );
}

void
handler( int sig )
{
    if( sig == SIGUSR1 )
    {
        no_sig = 0;
        printf( "Parent done\n" );
    }
}

int
main( int argc, char * argv[] )
{
    struct sigaction act;
    memset( &act, 0, sizeof( struct sigaction ) );
    act.sa_handler = handler;
    sigaction( SIGUSR1, &act, NULL );

    if( argc != 1 )
    {
        printf( "Usage: %s ", argv[ 0 ] );
        return 1;
    }

    int pid_res = fork();

    if( !pid_res )
    {
        child();
        return 0;
    }

    while( no_sig )
        ;

    return 0;
}

