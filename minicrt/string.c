#include "minicrt.h"

/* reverse: reverse string s in place */
void reverse(char s[]) {
  int c, i, j;
  for (i = 0, j = strlen(s) - 1; i < j; i++, j--) {
    c = s[i];
    s[i] = s[j];
    s[j] = c;
  }
}

void itoa(int n, char *s, int base) {
  char alphabet[] = "0123456789abcdef";
  int i, sign;
  if ((sign = n) < 0) { /* record sign */
    n = -n;             /* make n positive */
  }

                                  /* base = 10 or 16 */ 
  i = 0;
  do {                            /* generate digits in reverse order */
    s[i++] = alphabet[n % base];  /* get next digit */
  } while ((n /= base) > 0);        /* delete it */
  
  if (sign < 0) {
    s[i++] = '-';
  }
  
  s[i] = '\0';
  reverse(s);
}

int strcmp(const char *src, const char *dest) {
  for ( ; *src == *dest; src++, dest++) {
    if (*src == '\0')
      return 0;
  }

  return *src - *dest;
}


char *strcpy(char *dest, const char *src) {

  char *ret = dest;
  while (*dest++ = *src++);
  return ret;
}


unsigned int strlen(const char *str) {  
  unsigned int i = 0;
  while (*str++ != '\0') {
    ++i;
  }

  return i;
}