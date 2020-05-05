CFLAGS = -std=gnu11 -Wall -Werror -Wextra -O2
CC = gcc
SHMLIBS = -lrt

.PHONY: all clean

all: task1_a task1_b

clean:
	$(RM) task1 task2 task3

task1: task1_a.c
	$(CC) $(CFLAGS) -O -o $@ $^ $(SHMLIBS)
task2: task1_b.c
	$(CC) $(CFLAGS) -O -o $@ $^ $(SHMLIBS)

