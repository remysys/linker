all: syscall int80 perf

syscall: syscall.o
	ld syscall.o -o syscall

syscall.o: syscall.s
	as -o syscall.o syscall.s


int80: int80.o
	ld int80.o -o int80

int80.o: int80.s
	as -o int80.o int80.s

perf: perf.c
	gcc -o perf perf.c

test:
	time ./perf 1 && \
	time ./perf 2 && \
	time ./perf 3
clean:
	rm -f syscall int80 syscall.o int80.o perf linux.vdso