CFLAGS = -std=gnu11 -Wextra -Wall -pedantic
CC = gcc
SHMLIBS = -lrt -lpthread

.PHONY: all clean

SOURCES = task1 task1_iter task2 task3 task3_atomic
all: $(SOURCES)

clean:
	$(RM) $(SOURCES)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(SHMLIBS)