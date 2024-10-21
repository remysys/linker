/*
 * gcc -m32 -g max_heap_size.c -o max_heap_size32
 * gcc -g max_heap_size.c -o max_heap_size64
*/
#include <stdio.h>
#include <stdlib.h>

unsigned long long maximum = 0;

int main(int argc, char* argv[]) {

  unsigned long long blocksize[] = { 1024 * 1024 * 1024, 1024 * 1024, 1024, 1 };
  unsigned long long i, count;

  // printf("unsigned long long size: %u\n", sizeof(unsigned long long));
  for (i = 0; i <= 3; i++) {
    for (count = 1;; count++) {
      void* block = malloc(maximum + blocksize[i] * count);
      if (block) {
        maximum = maximum + blocksize[i] * count;
        printf("maximum: %llu\n", maximum);
        free(block);
      } else {
        break;
      }
    }
  }

  printf("maximum malloc size = %llu bytes\n", maximum);

  return 0;
}