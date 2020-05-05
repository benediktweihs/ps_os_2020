CFLAGS = -std=gnu11 -Wextra -Wall -pedantic
CC = gcc
SHMLIBS = -lrt -lpthread

.PHONY: all clean

SOURCES = task1 task2 philosophers
all: $(SOURCES)

clean:
	$(RM) $(SOURCES)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(SHMLIBS)