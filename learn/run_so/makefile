# gcc -m32 -g -fPIC -shared -o lib.so lib.c
# gcc -m32 -g -ldl runso.c -o runso
# ./runso ./lib.so foobar i2 i
# objdump -S runso > 1.txt

CC = gcc

CFLAGS = -m32 -g 
LDFLAGS = -ldl
SHAREDFLAGS = -fPIC -shared

all: lib.so runso

lib.so: lib.c
	$(CC) $(CFLAGS) $(SHAREDFLAGS) -o lib.so lib.c

runso: runso.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o runso runso.c

clean:
	rm -f lib.so runso