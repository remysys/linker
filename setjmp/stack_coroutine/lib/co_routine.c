
#include <stdio.h>
#include <stdlib.h>
#include "co_routine.h"

task_t *cur_task = 0;

void add_task(ctx_t *ctx, task_t *buf,  void *stack_bottom, size_t stack_size, void(*call)()) {
  // save the function pointer for when we start the task
  buf->call = call;
  
  // calculate the stack top
  
  buf->stack_top = (uint64_t *) ((char *)stack_bottom + stack_size);
  
  // ctx acts as a pointer to the first task in our list
  if (!*ctx) {
    *ctx = buf;
    buf->next = buf->prev = buf;
  } else {
    // link the task to the last
    task_t *last = (*ctx)->prev;

    buf->next = *ctx;
    (*ctx)->prev = buf;

    buf->prev = last;
    last->next = buf;
  }
}

void schedule_task(ctx_t *ctx) {
  cur_task = *ctx;
  while (1) {
    // save scheduler state
    int ret = co_setjmp(cur_task->ctx_env);

    if (0 == ret) {
      if (!cur_task->called) {
        cur_task->called = 1;
        // set stack pointer to task's stack eg. switch stack
        stack_pointer = (uint64_t)cur_task->stack_top;
        // call task
        cur_task->call();
      } else {
        // restore previous task state
        co_longjmp(cur_task->func_env, 1);
      }
    }
    
    if (ret > 1) { // dump
      // are we in the last task?
      if (cur_task->next == cur_task)
          break;

      task_t *prev = cur_task->prev;
      task_t *next = cur_task->next;

      // if we are in the first task, update that
      if (*ctx == cur_task)
          *ctx = next;

      // unlink current task
      prev->next = next;
      next->prev = prev;
    }
    // move on to next task
    cur_task = cur_task->next;
  }
}