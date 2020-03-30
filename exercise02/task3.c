#define _POSIX_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h> // fork
#include <unistd.h>    // sleep, getpid
#include <sys/wait.h>  // wait
#include <signal.h>
#include <string.h>
int child_SIGUSR2 = 0;
int not_child_done = 1;
int sent_SIGURS2 = 0;
int pid;

void
handler_child( int sig );

void
child()
{
    alarm( 13 );
    struct sigaction act;
    memset( &act, 0, sizeof( struct sigaction ) );
    act.sa_handler = handler_child;
    sigaction( SIGUSR1, &act, NULL );
    sigaction( SIGUSR2, &act, NULL );
    sigaction( SIGALRM, &act, NULL );

    while( not_child_done )
        ;
}

void
handler_parent( int sig )
{
    if( sig == SIGUSR1 )
    {
        not_child_done = 0;
        printf( "Parent done\n" );
    }
    if( sig == SIGALRM )
    {
        if( !sent_SIGURS2 )
        {
            sent_SIGURS2 = 1;
            kill( pid, SIGUSR2 );
        }

        kill( pid, SIGUSR1 );
        alarm( 3 );
    }
}

void
handler_child( int sig )
{
    if( sig == SIGUSR1 )
    {
        printf( "Received SIGUSR1\n" );
    }
    if( sig == SIGUSR2 )
    {
        child_SIGUSR2 = 1;
    }
    if( sig == SIGALRM && child_SIGUSR2 )
    {
        printf( "Child done\n" );
        child_SIGUSR2 = 0;
        kill( getppid(), SIGUSR1 );
    }
}

int
main( int argc, char * argv[] )
{
    alarm( 3 );

    if( argc != 1 )
    {
        printf( "Usage: %s ", argv[ 0 ] );
        return 1;
    }

    pid = fork();

    if( !pid )
    {
        child();
        return 0;
    }

    struct sigaction act_par;
    memset( &act_par, 0, sizeof( struct sigaction ) );
    act_par.sa_handler = handler_parent;
    sigaction( SIGUSR1, &act_par, NULL );
    sigaction( SIGUSR2, &act_par, NULL );
    sigaction( SIGALRM, &act_par, NULL );

    while( not_child_done )
        ;
    return 0;
}
