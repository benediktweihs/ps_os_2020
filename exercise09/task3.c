//
// Created by benedikt on 26.05.20.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dlfcn.h>
#include <pthread.h>
#include <stdbool.h>
#define MAXLEN 256

void* memSegment;
int T;
pthread_mutex_t lockMem;
pthread_mutex_t lockFree;


__thread void* (*my_malloc)(int, int, void*, bool*);
__thread void* (*my_free)(void*, int, int, void*, bool*);

typedef struct passData {
    int N;
    int id;
    int S;
	void* handler;
    bool* blocks;
} passData;

void error(char msg[MAXLEN]){
    printf("Error: %s\n", msg);
    exit(EXIT_FAILURE);
}

void* exec(void* args) {
    passData* data = (passData*) args;
    int N = data->N;
    //int id = data->id;
    int S = data->S;
	void* handle = data->handler;
    bool* blocks = data->blocks;
    void* partial;
	
    my_malloc = (void* (*)(int, int, void*, bool*)) dlsym(handle, "my_malloc");
    my_free = (void* (*)(void*, int, int, void*, bool*)) dlsym(handle, "my_free");


    for(int i = 0; i < N; i++){
        //  critical section - (de)allocate memory
        pthread_mutex_lock(&lockMem);
        partial = (void*) my_malloc(T, S, memSegment, blocks);
        pthread_mutex_unlock(&lockMem);
        pthread_mutex_lock(&lockFree);
        my_free(partial, T, S, memSegment, blocks);
        pthread_mutex_unlock(&lockFree);
    }

    return NULL;
}

int main(int argc, char* argv[]){
    if(argc != 5){
        error("4 additional args needed");
    }
    // initialize pthread_mutex
    if(pthread_mutex_init(&lockMem, NULL)) error("Mutex init gone wrong");
    if(pthread_mutex_init(&lockFree, NULL)) error("Mutex init gone wrong");

    // input:
    char sharedLib[MAXLEN];
    strcpy(sharedLib, argv[1]);
    char* ptr;
    int N, S;
    T = (int) strtol(argv[2], &ptr, 10);
    N = (int) strtol(argv[3], &ptr, 10);
    S = (int) strtol(argv[4], &ptr, 10);
    //bool *blocks = (bool*) malloc(T * sizeof(bool));

    //for(int i = 0; i < T; i++) blocks[i] = false;

    // create block of memory to operate in
    memSegment = malloc((size_t) S*T*N);

    void* handle = dlopen(sharedLib, RTLD_LAZY);
    if(!handle){
        pthread_mutex_destroy(&lockMem);
        pthread_mutex_destroy(&lockFree);
        error("Not able to access shared library");
    }

    // pointer to a function that takes size_t as an arg and returns a pointer to void
    bool *blocks = (bool*) malloc(N*T * sizeof(bool));
    // store thread ids
    pthread_t ids[T];
    passData data[T];
    for(int i = 0; i < T; i++) {
        (data + i)->N = N;
        (data + i)->id = i;
        (data + i)->S = S;
        (data + i)->handler = handle;
        (data + i)->blocks = blocks;
        ids[i] = i;
    }

    // thread creation
    for(int i = 0; i < T; i++) {
        if(pthread_create(ids + i, NULL, &exec, (void*)(data + i))) goto cleanup;
    }

    // wait or all threads to finish
    for(int i = 0; i < T; i++) {
        if(pthread_join(*(ids + i), NULL)) goto cleanup;
    }

    free(memSegment);
    free(blocks);
    dlclose(handle);
    pthread_mutex_destroy(&lockMem);
    pthread_mutex_destroy(&lockFree);

    return EXIT_SUCCESS;

    cleanup:
    free(memSegment);
    free(blocks);
    dlclose(handle);
    pthread_mutex_destroy(&lockMem);
    pthread_mutex_destroy(&lockFree);
    error("Poisx thread command failed");
}