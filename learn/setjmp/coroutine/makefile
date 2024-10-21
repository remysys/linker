CC = gcc
NASM = nasm
CFLAGS = -std=c11

all: co_test

lib/co_routine.o: lib/co_routine.c lib/co_routine.h
	$(CC) $(CFLAGS) -c -o lib/co_routine.o lib/co_routine.c

co_routine.a: lib/co_routine.o
	ar rcs co_routine.a lib/co_routine.o

co_test: co_routine.a co_test.c
	$(CC) $(CFLAGS) -o co_test co_test.c co_routine.a

clean:
	rm -f co_test co_routine.a lib/co_routine.o