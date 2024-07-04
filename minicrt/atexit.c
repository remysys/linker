#include "minicrt.h"

typedef struct _func_node {
  atexit_func_t func;
  void* arg;
  int is_cxa;
  struct _func_node* next;
} func_node;

static func_node* atexit_list = 0;

int register_atexit(atexit_func_t func, void *arg, int is_cxa) {
    func_node* node;
    if (!func) return -1;

    node = (func_node *)malloc(sizeof(func_node));
    
    if(node == 0) return -1;

    node->func = func;
    node->arg = arg;
    node->is_cxa = is_cxa;
    node->next = atexit_list;
    atexit_list = node;
    return 0;
}

int __cxa_atexit(cxa_func_t func, void *arg, void *unused) {
  return register_atexit((atexit_func_t)func, arg, 1);
}

int atexit(atexit_func_t func) {
  return register_atexit(func, 0, 0);
}

void mini_crt_call_exit_routine() {
  func_node* p = atexit_list;

  while (p != 0) {
    if (p->is_cxa)
        ((cxa_func_t)p->func)(p->arg);
    else
        p->func();

    func_node *t = p;
    p = p->next;
    
    free(t);
  }

  atexit_list = 0;
}