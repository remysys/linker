/*
#include <stdio.h>

extern char __executable_start[];
extern char etext[], _etext[], __etext[];
extern char edata[], _edata[];
extern char end[], _end[];

int main() {
  printf("Executable Start %p\n", __executable_start);
  printf("Text End %p %p %p\n", etext, _etext, __etext);
  printf("Data End %p %p\n", edata, _edata);
  printf("Executable End %p %p\n", end, _end);

  return 0;
} */


// https://stackoverflow.com/questions/1765969/where-are-the-symbols-etext-edata-and-end-defined

// this is a code from Linux man page:
#include <stdio.h>
#include <stdlib.h>

extern char etext, edata, end;
extern char __executable_start;

int main() {
  printf("First address past:\n");
  printf("    executable start          %10p\n", &__executable_start);
  printf("    program text (etext)      %10p\n", &etext);
  printf("    initialized data (edata)  %10p\n", &edata);
  printf("    uninitialized data (end)  %10p\n", &end);

  exit(EXIT_SUCCESS);
}