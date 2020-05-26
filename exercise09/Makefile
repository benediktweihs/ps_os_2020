CFLAGS = -std=gnu11 -Wall -Werror
CC = gcc
SHMLIBS = -lrt -lpthread -ldl

.PHONY: all clean

SOURCES = system_allocator.o task2.o system_allocator.so task2.so membench
all: $(SOURCES)

libs: $(LIBS).o $(LIBS).so
system_allocator.o : system_allocator.c
	$(CC) $(CFLAGS) -fpic -c system_allocator.c
	$(CC) $(CFLAGS) -fpic -c system_allocator.c
task2.o : task2.c
	$(CC) $(CFLAGS) -fpic -c task2.c
system_allocator.so : system_allocator.o
	$(CC) $(CFLAGS) -shared -o system_allocator.so system_allocator.o
task2.so : task2.o
	$(CC) $(CFLAGS) -shared -o task2.so task2.o
membench : membench.c
	$(CC) $(CFLAGS) -o membench membench.c $(SHMLIBS)
clean:
	rm -rf $(SOURCES)
