CC = gcc
CFLAGS = -fPIC
LDFLAGS = -shared

LIBRARY = lib.so
PROGRAMS = program1 program2

all: $(LIBRARY) $(PROGRAMS)

$(LIBRARY): lib.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^


program1: program1.c $(LIBRARY)
	$(CC) -o program1 program1.c ./$(LIBRARY)
	
program2: program2.c $(LIBRARY)
	$(CC) -o program2 program2.c ./$(LIBRARY)

.PHONY: clean
clean:
	rm -f $(PROGRAMS) $(LIBRARY)
