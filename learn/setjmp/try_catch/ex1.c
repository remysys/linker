// gcc ex1.c
// http://groups.di.unipi.it/~nids/docs/longjump_try_trow_catch.html
#include <stdio.h>
#include <setjmp.h>

#define TRY do { jmp_buf ex_buf__; if (!setjmp(ex_buf__)) {
#define CATCH } else {
#define ETRY }} while(0)
// end of try-throw-catch block
#define THROW longjmp(ex_buf__, 1)

int main(int argc, char** argv) {
  TRY {
    printf("in try block\n");
    THROW;
    printf("i do not appear\n");
  } CATCH {
    printf("got exception\n");
  }
  ETRY;

  return 0;
}