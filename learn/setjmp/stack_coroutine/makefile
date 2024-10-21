CC = gcc
AS = as
CFLAGS = -std=c11 -g

all: co_test


lib/co_jmp_asm.o: lib/co_jmp.s
	$(AS) -o lib/co_jmp_asm.o lib/co_jmp.s

lib/co_jmp.o: lib/co_jmp.c
	$(CC) $(CFLAGS) -c -o lib/co_jmp.o lib/co_jmp.c

lib/co_routine.o: lib/co_routine.c lib/co_routine.h
	$(CC) $(CFLAGS) -c -o lib/co_routine.o lib/co_routine.c

lib/co_routine.a: lib/co_jmp_asm.o lib/co_jmp.o lib/co_routine.o 
	ar rcs lib/co_routine.a lib/co_jmp.o lib/co_jmp_asm.o lib/co_routine.o

co_test: lib/co_routine.a co_test.c
	$(CC) $(CFLAGS) -o co_test co_test.c lib/co_routine.a

clean:
	rm -f co_test lib/co_routine.a lib/co_jmp.o lib/co_jmp_asm.o lib/co_routine.o