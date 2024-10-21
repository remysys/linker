#gcc -fPIC -shared a1.c -o a1.so
#gcc -fPIC -shared a2.c -o a2.so
#gcc -fPIC -shared b1.c a1.so -o b1.so
#gcc -fPIC -shared b2.c a2.so -o b2.so
#gcc main.c b1.so b2.so -o main 

CC = gcc
CFLAGS = -fPIC
LDFLAGS = -L.

all: main

a1.so: a1.c
	gcc -fPIC -shared $^ -o $@

a2.so: a2.c
	gcc -fPIC -shared $^ -o $@

b1.so: b1.c a1.so
	gcc -fPIC -shared $^ -o $@

b2.so: b2.c a2.so
	gcc -fPIC -shared $^ -o $@

main: main.c b1.so b2.so
	gcc $^ -o $@ -Wl,-rpath=.

clean:
	rm -f a1.so a2.so b1.so b2.so main

