//
// Created by benedikt on 26.05.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void* my_malloc(int T, int S, void* segment, bool* blocks){
	return malloc((size_t) S);
}

void my_free(void* ptr, int T, int S, void* segment, bool* blocks){
	return free(ptr);
}