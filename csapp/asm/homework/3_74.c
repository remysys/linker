/*
 * write a function in assembly code that matches the behavior of the function find_
 * range in Figure 3.51. Your code should contain only one floating-point comparison
 * instruction, and then it should use conditional moves to generate the correct result.
 * You might want to make use of the instruction cmovp (move if even parity). Test
 * your code on all 232 possible argument values. Web Aside asm:easm on page 214
 * describes how to incorporate functions written in assembly code into C programs.
 * 
 * .global find_range
 * 
 * find_range:
 *  vxorps %xmm1, %xmm1, %xmm1
 *  movq $1, %rax
 *  movq $2, %r8
 *  movq $0, %r9 
 *  movq $3, %r10
 *  vucomiss %xmm1, %xmm0
 *  cmovaq %r8, %rax
 *  cmovbq %r9, %rax
 *  cmovpq %r10, %rax
 *  retq
 */

#include <stdio.h>

__asm__ (
 ".global find_range\n"
 "find_range:\n"
 "vxorps %xmm1, %xmm1, %xmm1\n"
 "movq $1, %rax\n"
 "movq $2, %r8\n"
 "movq $0, %r9\n"
 "movq $3, %r10\n"
 "vucomiss %xmm1, %xmm0\n"
 "cmovaq %r8, %rax\n"
 "cmovbq %r9, %rax\n"
 "cmovpq %r10, %rax\n"
 "retq\n"
);

long find_range(float x);

int main() {
  float vals[] = {0.0, -3.5, 5.0, 0.0/0.0}; // include nan
  char* str[] = {"negative", "zero", "positive", "nan"};

  int i;
  for (i = 0; i < 4; i++) {
    long res = find_range(vals[i]);
    printf("find_range(%f) = %s\n", vals[i], str[res]);
  }

  return 0;
}