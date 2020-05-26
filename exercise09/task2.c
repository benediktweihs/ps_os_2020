//
// Created by benedikt on 26.05.20.
//
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct storeLocation{
	int i;
} storeLocation;

void* my_malloc(int T, int S, void* segment, bool* blocks){
	int max = 0;
	int highLow = 0;
	int highUp = 0;
	int highOverall = 0;
	int index = 0;
	int firstFree = 0;
	bool low = true;
	bool inGap = false;

    for(int i = 0; i < T; i++){
		if(blocks[i]){
			inGap = false;
			max++;
			continue;
		}
		// Gap in memory alloc
		if(!blocks[i] && !inGap){
            if(!low) highUp = max;
            else highLow = max;
            if(highLow+highUp>highOverall){
                highOverall = highLow + highUp;
                index = firstFree+1;
            }
            inGap = true;
            max = 0;
            low = false;
            firstFree = i;
        }
	}
	blocks[index] = true;
	//printf("%d\n", index);
	return (void*) blocks+index;
}

void my_free(void* ptr, int T, int S, void* segment, bool* blocks){
	bool* myBool = (bool*) ptr;
	*myBool = false;
}
