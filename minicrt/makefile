# minicrt
# gcc -c -m32 -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c printf.c stdio.c string.c 
# ar rcs minicrt.a malloc.o printf.o stdio.o string.o
# gcc -c -m32 -fno-builtin -nostdlib -fno-stack-protector test.c 
# ld -m elf_i386 -static -e mini_crt_entry entry.o test.o minicrt.a -o test

# minicrt++
# gcc -c -m32 -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c printf.c stdio.c string.c atexit.c
# g++ -c -m32 -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector crtbegin.cpp crtend.cpp ctor.cpp new_delete.cpp iostream.cpp cstring.cpp sysdep.cpp
# ar rcs minicrt.a malloc.o printf.o stdio.o string.o ctor.o atexit.o iostream.o new_delete.o cstring.o sysdep.o
# g++ -c -m32 -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector test.cpp
# ld -m elf_i386 -static -e mini_crt_entry entry.o crtbegin.o test.o minicrt.a crtend.o -o test

CC = gcc
CXX = g++
CFLAGS = -c -m32 -g -fno-builtin -nostdlib -fno-stack-protector
CXXFLAGS = -c -m32 -g -nostdinc++ -fno-rtti -fno-exceptions -fno-builtin -nostdlib -fno-stack-protector
LDFLAGS = -m elf_i386 -static -e mini_crt_entry

COBJS = entry.o malloc.o printf.o stdio.o string.o atexit.o 
CXXOBJS = crtbegin.o crtend.o ctor.o new_delete.o iostream.o cstring.o sysdep.o test.o
CRTOBJS = malloc.o printf.o stdio.o string.o atexit.o ctor.o iostream.o new_delete.o cstring.o sysdep.o

CSRCS = $(COBJS:.o=.c) 
CXXSRCS = $(CXXOBJS:.o=.cpp)

CRTLIB = minicrt.a
TARGET = test

.PHONY: all clean

all: $(TARGET)


test: entry.o crtbegin.o test.o $(CRTLIB) crtend.o
	ld $(LDFLAGS) entry.o crtbegin.o test.o $(CRTLIB) crtend.o -o test

$(CRTLIB): $(CRTOBJS)
	ar rcs $@ $^

$(COBJS): $(CSRCS)
	$(CC) $(CFLAGS) $(@:.o=.c) -o $@

$(CXXOBJS): $(CXXSRCS)
	$(CXX) $(CXXFLAGS) $(@:.o=.cpp) -o $@

clean:
	rm -f $(COBJS) $(CXXOBJS) $(CRTLIB) $(TARGET)
