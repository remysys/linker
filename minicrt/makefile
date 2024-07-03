# gcc -c -m32 -fno-builtin -nostdlib -fno-stack-protector entry.c malloc.c printf.c stdio.c string.c 
# ar rcs minicrt.a malloc.o printf.o stdio.o string.o
# gcc -c -m32 -fno-builtin -nostdlib -fno-stack-protector test.c 
# ld -m elf_i386 -static -e mini_crt_entry entry.o test.o minicrt.a -o test

CC = gcc
LD = ld
CFLAGS = -c -m32 -fno-builtin -nostdlib -fno-stack-protector
LDFLAGS = -m elf_i386 -static -e mini_crt_entry

SRCS = entry.c malloc.c printf.c stdio.c string.c test.c
OBJS = $(SRCS:.c=.o)
LIB = minicrt.a
TARGET = test

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(OBJS) $(LIB)
	$(LD) $(LDFLAGS) entry.o $(LIB) -o $@

$(LIB): $(filter-out entry.o, $(OBJS))
	ar rcs $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJS) $(LIB) $(TARGET)