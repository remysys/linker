#ifndef _CO_ROUTINE_H_
#define _CO_ROUTINE_H_

#include "co_jmp.h"

typedef struct task {
  void (*call)();         // the function that starts the task
  int called;             // whether we already called the above function
  void *stack_top;        // pointer to the top of the stack memory
  co_jmp_buf func_env;    // data to jump back into the task
  co_jmp_buf ctx_env;     // data to jump back to the scheduler
  struct task *next;      // next in linked list
  struct task *prev;      // previous in linked list
} task_t;

typedef task_t *ctx_t;

task_t *get_last(task_t *first);

// add a task to the task queue
void add_task(ctx_t *ctx, task_t *buf,  void *stack_bottom, size_t stack_size, void(*call)());

// runs all the task asynchronously
void start(ctx_t *ctx);

extern task_t *cur_task;

#define yield if (!co_setjmp(cur_task->func_env)) \
    co_longjmp(cur_task->ctx_env, 1)
#define dump if (!co_setjmp(cur_task->func_env)) \
    co_longjmp(cur_task->ctx_env, 2)

#endif