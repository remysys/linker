.section .text

.global _co_setjmp_asm
.global _co_longjmp_asm

_co_setjmp_asm:

  /*
   * buf will be in rax
   * rbx rsp rbp and r12-r15 are callee saved
   * the other registers have to be saved by
   * the caller anyways so we can just ignore them

   * save the registers
   * todo: we don't save the flags register here
   *       we could get it using pushf and then
   *       restore with popf, but that's quite slow
   *       https://stackoverflow.com/q/1406783
   */

  movq %rbx, 0(%rax)
  movq %rcx, 8(%rax)
  movq %rsi, 16(%rax)
  movq %rdi, 24(%rax)
  movq %rbp, 32(%rax)
  movq %r8,  40(%rax)
  movq %r9,  48(%rax)
  movq %r10, 56(%rax)
  movq %r11, 64(%rax)
  movq %r12, 72(%rax)
  movq %r13, 80(%rax)
  movq %r14, 88(%rax)
  movq %r15, 96(%rax)

  /*
   * save the address rsp + 24
   * 24 because we have three 8 byte values to store
   * later on. 24 is safe because we have at least
   * 1) the return address to the original caller
   * 2) the stack base pushed by the compiler
   * 3) the return address to the wrapper function
   * /
  leaq 24(%rsp), %rdx
  movq %rdx, 104(%rax)

  /*
   * the next three blocks are basically just
   * saving the important part of the stack since
   * it is likely to be overwritten by variables
   * after we return

  
  // save the return address to the wrapper function
  movq (%rsp), %rdx
  movq %rdx, 112(%rax)

  // save the stack base of the original caller
  movq (%rbp), %rdx
  movq %rdx, 120(%rax)

  // save the return address to the original caller
  movq 8(%rbp), %rdx
  movq %rdx, 128(%rax)

  /*
   * setjmp needs to return 0, if it doesn't return from a
   * longjmp. xor rdx, rdx is just a fancy way of writing
   * mov rdx, 0 which is a bit faster
   */

  xorq %rdx, %rdx
  ret

_co_longjmp_asm:
    
  /*
    * buf will be in rax
    * ret will be in rdx
    */

  // restore rsp
  movq 104(%rax), %rsp
  
  // restore the return address to the original caller
  pushq 128(%rax)

  // restore the stack base of the original caller
  pushq 120(%rax)

  // restore the return address to the wrapper function
  pushq 112(%rax)

  // restore the registers

  movq 0(%rax), %rbx
  movq 8(%rax), %rcx
  movq 16(%rax), %rsi
  movq 24(%rax), %rdi
  movq 32(%rax), %rbp
  movq 40(%rax), %r8
  movq 48(%rax), %r9
  movq 56(%rax), %r10
  movq 64(%rax), %r11
  movq 72(%rax), %r12
  movq 80(%rax), %r13
  movq 88(%rax), %r14
  movq 96(%rax), %r15
  ret
