// gcc ex3.c 
// http://groups.di.unipi.it/~nids/docs/longjump_try_trow_catch.html

// Duff's device
// http://catb.org/jargon/html/D/Duffs-device.html

#include <stdio.h>
#include <setjmp.h>

#define TRY do { jmp_buf ex_buf__; switch(setjmp(ex_buf__)) { case 0: while(1) {
#define CATCH(x) break; case x:
#define FINALLY break; } default:
#define ETRY }} while(0)
#define THROW(x) longjmp(ex_buf__, x)

#define FOO_EXCEPTION (1)
#define BAR_EXCEPTION (2)
#define BAZ_EXCEPTION (3)

int main(int argc, char** argv) {
  TRY {
    printf("in try block\n");
    THROW(BAR_EXCEPTION);
    printf("i do not appear\n");
  } CATCH(FOO_EXCEPTION) {
    printf("got foo\n");
  } CATCH(BAR_EXCEPTION) {
    printf("got bar\n");
  } CATCH(BAZ_EXCEPTION) {
    printf("got baz\n");
  } FINALLY {
    printf("...et in arcadia ego\n");
  }
  ETRY;

  return 0;
}