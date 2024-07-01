/* time consume: emulated vsyscall > normal syscall > vDSO syscall 
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

 * cat /usr/src/linux-headers-$(uname -r)/.config | grep VSYSCALL
 * apt update
 * uname -r
 * apt install linux-headers-6.1.0-18-amd64
 * https://solariar.net/notes/syscall.html#x86%E6%9E%B6%E6%9E%84%E7%B3%BB%E7%BB%9F%E8%B0%83%E7%94%A8%E5%AE%9E%E7%8E%B0%E6%A6%82%E8%BF%B0
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
    for (i = 0; i < 1000000; ++i) /* syscall */
      syscall(SYS_time, NULL);
  }

  return 0;

}