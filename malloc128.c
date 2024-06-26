#include <stdio.h>
#include <malloc.h>

int main() {
  // allocate 128k mem
  void *addr = malloc(128*1024);
  printf("start address: %x\n", addr);

  printf("cat /proc/%d/maps\n",getpid());

  getchar();

  // free mem
  free(addr);
  printf("128KB of memory has been released, and the memory has been returned to the operating system.\n");

  getchar();
  return 0;
}