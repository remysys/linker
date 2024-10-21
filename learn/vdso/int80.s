/*
 * as -o int80.o int80.s
 * ld int80.o
 */

.data
    s: .ascii "hello world\n"
    len = . - s
.text
  .global _start
  _start:
    movl $4, %eax   /* write system call number */
    movl $1, %ebx   /* stdout */
    movl $s, %ecx   /* the data to print */
    movl $len, %edx /* length of the buffer */
    int $0x80

    movl $1, %eax   /* call exit(0) */
    movl $0, %ebx   /* exit status */
    int $0x80
