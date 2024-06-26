// clang loop_unroll.c
// gcc -std=c99 loop_unroll.c
#include <stdio.h>
#include <sys/time.h>

int main() {
  int sum = 0;
  struct timeval start, end;
  gettimeofday(&start, NULL);

  // iterate 100,000,000 times
  for (int i = 0; i < 100000000; i++) {
    sum += i;
  }

  gettimeofday(&end, NULL);
  // ms
  long duration = (end.tv_sec - start.tv_sec) * 1000 +
                        (end.tv_usec - start.tv_usec) / 1000;
  printf("normal-iterate sum: %d, duration: %ld ms\n", sum, duration);

  sum = 0;
  gettimeofday(&start, NULL);

  // unroll the loop 5 times each iteration, requiring only 20,000,000 iterations
  for (int i = 0; i < 100000000; i += 5) {
    sum += i;
    sum += i + 1;
    sum += i + 2;
    sum += i + 3;
    sum += i + 4;
  }

  gettimeofday(&end, NULL);
  // ms
  duration = (end.tv_sec - start.tv_sec) * 1000 +
                        (end.tv_usec - start.tv_usec) / 1000;
  printf("unroll-iterate sum: %d, duration: %ld ms\n", sum, duration);

  return 0;
}