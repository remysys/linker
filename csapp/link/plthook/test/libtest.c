#include <stdlib.h>
#include "libtest.h"

double strtod_cdecl(const char *str, char **endptr) {
  return strtod(str, endptr);
}