/*
 * write a function in assembly code that matches the behavior of the function find_
 * range in Figure 3.51. Your code should contain only one floating-point comparison
 * instruction, and then it should use conditional branches to generate the correct
 * result. Test your code on all 232 possible argument values. Web Aside asm:easm
 * on page 214 describes how to incorporate functions written in assembly code into
 * C programs.

* .global find_range
* 
* find_range:
*     vxorps      %xmm1, %xmm1, %xmm1
*     vucomiss    %xmm1, %xmm0
*     jp          nan
*     jb          neg
*     jz          zero
*     movq        $2, %rax
*     retq
* nan:
*     movq        $3, %rax
*     retq
* neg:
*     xorq        %rax, %rax
*     retq
* zero:
*     movq        $1, %rax
*     retq
*/

#include <stdio.h>

__asm__ (
  ".global find_range\n"
  "find_range:\n"
  "vxorps %xmm1, %xmm1, %xmm1\n"
  "vucomiss %xmm1, %xmm0\n"
  "jp nan\n"
  "jb neg\n"
  "jz zero\n"
  "movq $2, %rax\n"
  "retq\n"
  "nan:\n"
  "movq $3, %rax\n"
  "retq\n"
  "neg:\n"
  "xorq %rax, %rax\n"
  "retq\n"
  "zero:\n"
  "movq $1, %rax\n"
  "retq\n"
);

long find_range(float x);

int main() {
  float vals[] = {0.0, -3.5, 5.0, 0.0/0.0}; // include NaN
  char* str[] = {"negative", "zero", "positive", "nan"};

  int i;
  for (i = 0; i < 4; i++) {
    long res = find_range(vals[i]);
    printf("find_range(%f) = %s\n", vals[i], str[res]);
  }

  return 0;
}