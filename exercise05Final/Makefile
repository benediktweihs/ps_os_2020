CFLAGS = -std=gnu11 -Wall -Werror -Wextra -O2 -pedantic
CC = gcc
SHMLIBS = -lrt -lpthread

.PHONY: all clean

SOURCES = task1_a task1_b task2_a task2_b
all: $(SOURCES)

clean:
	$(RM) $(SOURCES)

%: %.c
	$(CC) $(CFLAGS) -o $@ $^ $(SHMLIBS)

