#include <stdio.h>
#include <stdlib.h>
#include "lib/co_routine.h"

void my_async_func() {
  puts("Func1: 1");
  yield;
  puts("Func1: 2");
  dump;
}

void my_async_func2() {
  puts("Func2: 1");
  yield;
  puts("Func2: 2");
  dump;
}

int main() {
  ctx_t ctx = 0;
  task_t t1 = {0}, t2 = {0};
  add_task(&ctx, &t1, malloc(4096), 4096, my_async_func);
  add_task(&ctx, &t2, malloc(4096), 4096, my_async_func2);
  start(&ctx);
  //free(t1.stack_top - 4096);
  //free(t2.stack_top - 4096);
  return 0;
}