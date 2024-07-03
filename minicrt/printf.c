#include "minicrt.h"

int fputc(int c, FILE *stream) {
  if (fwrite(&c, 1, 1, stream) != 1) {
    return EOF;
  } else{
    return c;
  }
}

int fputs(const char *str, FILE *stream) {
  int len = strlen(str);
  if (fwrite(str, 1, len, stream) != len) {
    return EOF;
  } else {
    return len;
  }
}

#define va_list char *
#define va_start(ap, arg) (ap = (va_list)&arg + sizeof(arg))
#define va_arg(ap, t)  (*(t*)((ap += sizeof(t)) - sizeof(t)))
#define va_end(ap) (ap=(va_list)0)

static int vfprintf(FILE *stream, const char *format, va_list ap) {
  int ret = 0;
  char buf[16];

  for (; *format; ++format) {
    if (*format == '%') {
      format++;
      if (*format == '%') {
        ++ret;
        fputc('%', stream);
        continue;
      }

      switch (*format) {
        case 's': 
          ret += fputs(va_arg(ap, char *), stream);
          break;
        case 'd':
          itoa(va_arg(ap, int), buf);
          ret += fputs(buf, stream);
          break;
        default:
          fputc(*format, stream);
          ret++;
          break;
      }
    } else {
      fputc(*format, stream);
      ret++;
    }
  }

  return ret;
}

int printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  return vfprintf(stdout, format, args);
}

int fprintf(FILE *stream, const char *format, ...) {
  va_list args;
  va_start(args, format);
  return vfprintf(stream, format, args);
}

