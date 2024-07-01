/* time consume: emulated vsyscall > native syscall > vDSO syscall 
 * vsys_call
 * 
 * vdso:
 * __vdso_clock_gettime;
 * __vdso_getcpu;
 * __vdso_gettimeofday;
 * __vdso_time.
 
 * vsyscall:
 * __vsyscall_page:
    mov $__NR_gettimeofday, %rax
    syscall
    ret

    .balign 1024, 0xcc
    mov $__NR_time, %rax
    syscall
    ret

    .balign 1024, 0xcc
    mov $__NR_getcpu, %rax
    syscall
    ret

    .balign 4096, 0xcc

    .size __vsyscall_page, 4096
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/syscall.h>

// time_t (*f)(time_t *tloc) = 0xffffffffff600400; 

typedef time_t (*FP)(time_t *tloc);

int main(int argc, char **argv) {
  if (argc != 2) {                      
    printf("time ./perf 1\ntime ./perf 2\ntime ./perf 3\n");
    exit(1);
  }

  int n = atoi(argv[1]);

  FP f = (FP)0xffffffffff600400; // __NR_time
  unsigned long i = 0;

  if (n == 1) {                   /* emulated vsyscall */
    for (i = 0; i < 1000000;++i)
      f(NULL);
  } else if (n == 2) {            /* vDSO syscall */
    for (i = 0; i < 1000000;++i)
      time(NULL);
  } else {
    for (i = 0; i < 1000000; ++i) /* native syscall */
      syscall(SYS_time, NULL);
  }

  return 0;

}