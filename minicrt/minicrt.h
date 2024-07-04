#ifndef _MINICRT_H_
#define _MINICRT_H_

#ifdef __cplusplus
extern "C" {
#endif

// malloc
#define NULL (0)

void free(void* ptr);
void *malloc(unsigned int size);
static void *brk(void *addr);
int mini_crt_init_heap();

// io
typedef int FILE;
#define EOF	(-1)

#define stdin	  ((FILE*)0)
#define stdout	((FILE*)1)
#define stderr	((FILE*)2)

int mini_crt_init_io();

FILE *fopen(const char *filename, const char *mode);
int fread(void *buffer, int size, int count, FILE *stream);
int fwrite(const void *buffer, int size, int count, FILE *stream);
int fclose(FILE *fp);
int fseek(FILE *fp, int offset, int set);

// string
void itoa(int n, char *s);
int strcmp(const char *src, const char *dest);
char *strcpy(char *dest, const char *src);
unsigned int strlen(const char *str);

// printf
int fputc(int c, FILE *stream);
int fputs(const char* str, FILE *stream);
int printf(const char *format, ...);
int fprintf(FILE *stream, const char *format, ...);

// atexit
typedef void (*cxa_func_t)(void *);
typedef void (*atexit_func_t)(void);
int __cxa_atexit(cxa_func_t func, void *arg, void *);
int atexit(atexit_func_t func);
void do_global_ctors();
void mini_crt_call_exit_routine();


#ifdef __cplusplus
}
#endif

#endif // _MINICRT_H_