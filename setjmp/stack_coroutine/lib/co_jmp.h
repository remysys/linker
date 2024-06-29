#ifndef _CO_JMP_H_
#define _CO_JMP_H_

typedef unsigned long long uint64_t;

// 64 bit
// low  +0   | buf[0]:  rbx |
//      +8   | buf[1]:  rcx |
//      +16  | buf[2]:  rsi |
//      +24  | buf[3]:  rdi |
//      +32  | buf[4]:  rbp |
//      +40  | buf[5]:  r8  |
//      +48  | buf[6]:  r9  |
//      +56  | buf[7]:  r10 |
//      +64  | buf[8]:  r11 |
//      +72  | buf[9]:  r12 |  
//      +80  | buf[10]: r13 |
//      +88  | buf[11]: r14 |
//      +96  | buf[12]: r15 |
//      +104 | buf[13]:  *  | // save the address: rsp + 24
//      +112 | buf[14]:  *  | // return address <-> in function co_setjmp + 4
//      +120 | buf[15]:  *  | // [rbp] <-> frame pointer of funciton which call co_setjmp
//hig   +128 | buf[16]:  *  | // return address <-> next instruction of call co_setjmp, eg. pursue_task + 1


typedef uint64_t co_jmp_buf[17];

int co_setjmp(uint64_t *buf);
void co_longjmp(uint64_t *buf, int ret);

#endif //_CO_JMP_H_