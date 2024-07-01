/*
 * as -o syscall.o syscall.s
 * ld syscall.o
 */

/*
1. User-level applications use as integer registers for passing the sequence %rdi, %rsi, %rdx, %rcx, %r8 and %r9. 
2. The kernel interface uses %rdi, %rsi, %rdx, %r10, %r8 and %r9.
3. A system-call is done via the syscall instruction. The kernel destroys registers %rcx and %r11.
4. The number of the syscall has to be passed in register %rax.
5. System-calls are limited to six arguments, no argument is passed directly on the stack.
6. Returning from the syscall, register %rax contains the result of the system-call. A value in the range between -4095 and -1 indicates an error, it is -errno.
7. Only values of class INTEGER or class MEMORY are passed to the kernel.
*/

.text 
  .global _start
  _start:
    movq $1, %rax             /* 1 is the number for syscall write () */
    movq $1, %rdi             /* 1 is the STDOUT file descriptor */
    movq $s,  %rsi            /* buffer to be printed */
    movq $len, %rdx           /* len of s */
    syscall

    movq $60, %rax              /* sys_exit */
    movq $0,  %rdi              /* return value is 0 */
    syscall

.data
  s: .ascii "hello world\n"
  len = . - s
