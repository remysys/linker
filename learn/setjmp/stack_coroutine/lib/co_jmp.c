#include "co_jmp.h"

int co_setjmp(uint64_t *buf) {
  int ret = 0;
  __asm__ volatile("movq %0, %%rax" : : "r" (buf));
  __asm__ volatile("call _co_setjmp_asm");
  __asm__ volatile("movl %%edx, %0" : : "m" (ret));
  return ret;
}

void co_longjmp(uint64_t *buf, int ret) {
  __asm__ volatile("mov %0, %%edx" : : "r" (ret));
  __asm__ volatile("movq %0, %%rax" : : "r" (buf));
  __asm__ volatile("jmp _co_longjmp_asm");
}
