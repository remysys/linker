
#include <stdlib.h>
#include "co_routine.h"


task_t *cur_task = 0;

task_t *get_last(task_t *first) {
  task_t *curr = first;
  while (curr->next != first) {
      curr = curr->next;
  }
  return curr;
}

// take control of the stack pointer
// register void *stack_pointer asm ("rsp");

int pursue_task() {
   // save scheduler state
  int ret = setjmp(cur_task->ctx_env);
  if (0 == ret) {
    if (!cur_task->called) {
      cur_task->called = 1;
      // set stack pointer to task's stack
      // stack_pointer = cur_task->stack_top;
      // call task
      cur_task->call();
    } else {
      // restore previous task state
      longjmp(cur_task->func_env, 1);
    }
  }

  return ret;
}

void add_task(ctx_t *ctx, task_t *buf,  void *stack_bottom, size_t stack_size, void(*call)()) {
  // save the function pointer for when we start the task
  buf->call = call;
  
  // calculate the stack top
  // buf->stack_top = (void *) (stack_bottom + stack_size);
  
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

void start(ctx_t *ctx) {
  cur_task = *ctx;
  while (1) {
    if (pursue_task() > 1) {
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