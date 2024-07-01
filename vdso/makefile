all: syscall int80

syscall: syscall.o
	ld syscall.o -o syscall

syscall.o: syscall.s
	as -o syscall.o syscall.s


int80: int80.o
	ld int80.o -o int80

int80.o: int80.s
	as -o int80.o int80.s

clean:
	rm -f syscall int80 syscall.o int80.o