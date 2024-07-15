#include <plthook.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "libtest.h"
#include <dlfcn.h>



#define CHK_PH(func) do { \
  if (func != 0) { \
      fprintf(stderr, "%s error: %s\n", #func, plthook_error()); \
      exit(1); \
  } \
} while (0)

typedef struct {
  const char *name;
  int enumerated;
} enum_test_data_t;

enum open_mode {
  OPEN_MODE_DEFAULT,
  OPEN_MODE_BY_HANDLE,
  OPEN_MODE_BY_ADDRESS,
};

static enum_test_data_t funcs_called_by_libtest[] = {
  {"strtod", 0},
  {NULL, },
};

static enum_test_data_t funcs_called_by_main[] = {
  {"strtod_cdecl", 0},
  {NULL, },
};

#define STRTOD_STR_SIZE 30

typedef struct {
    char str[STRTOD_STR_SIZE];
    double result;
} hooked_val_t;

/* value captured by hook from executable to libtest. */
static hooked_val_t val_exe2lib;
/* value captured by hook from libtest to libc. */
static hooked_val_t val_lib2libc;

static void reset_result(void) {
  val_exe2lib.str[0] = '\0';
  val_exe2lib.result = 0.0;
  val_lib2libc.str[0] = '\0';
  val_lib2libc.result = 0.0;
}

static void set_result(hooked_val_t *hv, const char *str, double result) {
  strncpy(hv->str, str, sizeof(hv->str));
  hv->result = result;
}

static void check_result(const char *str, double result, double expected_result, long line) {
  if (result != expected_result) {
    goto error;
  }
  if (strcmp(val_exe2lib.str, str) != 0) {
    goto error;
  }
  if (val_exe2lib.result != result) {
    goto error;
  }
  if (strcmp(val_lib2libc.str, str) != 0) {
    goto error;
  }
  if (val_lib2libc.result != result) {
    goto error;
  }
  return;
error:
  fprintf(stderr,
          "Error: ['%s', %f, %f] ['%s', %f] ['%s', %f] at line %ld\n",
          str, result, expected_result,
          val_exe2lib.str, val_exe2lib.result,
          val_lib2libc.str, val_lib2libc.result,
          line);
  exit(1);
}

#define CHK_RESULT(func_name, str, expected_result) do { \
  double result__; \
  reset_result(); \
  result__ = func_name(str, NULL); \
  check_result(str, result__, expected_result, __LINE__); \
} while (0)

static double (*strtod_cdecl_old_func)(const char *, char**);


/* hook func from libtest to libc. */
static double strtod_hook_func(const char *str, char **endptr) {
  double result = strtod(str, endptr);
  set_result(&val_lib2libc, str, result);
  return result;
}

/* hook func from testprog to libtest. */
static double strtod_cdecl_hook_func(const char *str, char **endptr) {
  double result = strtod_cdecl_old_func(str, endptr);
  set_result(&val_exe2lib, str, result);
  return result;
}

static void test_plthook_enum(plthook_t *plthook, enum_test_data_t *test_data) {
  unsigned int pos = 0;
  const char *name;
  void **addr;
  int i;

  while (plthook_enum(plthook, &pos, &name, &addr) == 0) {
    for (i = 0; test_data[i].name != NULL; i++) {
      if (strcmp(test_data[i].name, name) == 0) {
        test_data[i].enumerated = 1;
      }
    }
  }
  for (i = 0; test_data[i].name != NULL; i++) {
    if (!test_data[i].enumerated) {
      fprintf(stderr, "%s is not enumerated by plthook_enum.\n", test_data[i].name);
      pos = 0;
      while (plthook_enum(plthook, &pos, &name, &addr) == 0) {
        printf("   %s\n", name);
      }
      exit(1);
    }
  }
}

static void show_usage(const char *arg0) {
  fprintf(stderr, "Usage: %s (open | open_by_handle | open_by_address)\n", arg0);
}

static void hook_function_calls_in_executable(enum open_mode open_mode) {
  plthook_t *plthook;
  void *handle;

  switch (open_mode) {
    case OPEN_MODE_DEFAULT:
        CHK_PH(plthook_open(&plthook, NULL));
        break;
    case OPEN_MODE_BY_HANDLE:
        handle = dlopen(NULL, RTLD_LAZY);
        assert(handle != NULL);
        CHK_PH(plthook_open_by_handle(&plthook, handle));
        break;
    case OPEN_MODE_BY_ADDRESS:
        CHK_PH(plthook_open_by_address(&plthook, &show_usage));
        break;
  }
  test_plthook_enum(plthook, funcs_called_by_main);
  CHK_PH(plthook_replace(plthook, "strtod_cdecl", (void*)strtod_cdecl_hook_func, (void**)&strtod_cdecl_old_func));
  plthook_close(plthook);
}

static void hook_function_calls_in_library(enum open_mode open_mode) {
  plthook_t *plthook;
  void *handle;
  const char *filename = "libtest.so";
  void *address;

  switch (open_mode) {
    case OPEN_MODE_DEFAULT:
        CHK_PH(plthook_open(&plthook, filename));
        break;
    case OPEN_MODE_BY_HANDLE:
        handle = dlopen(filename, RTLD_LAZY | RTLD_NOLOAD);
        assert(handle != NULL);
        CHK_PH(plthook_open_by_handle(&plthook, handle));
        break;
    case OPEN_MODE_BY_ADDRESS:
        handle = dlopen(filename, RTLD_LAZY | RTLD_NOLOAD);
        address = dlsym(handle, "strtod_cdecl");
        assert(address != NULL);
        CHK_PH(plthook_open_by_address(&plthook, (char*)address));
        break;
  }
  test_plthook_enum(plthook, funcs_called_by_libtest);
  CHK_PH(plthook_replace(plthook, "strtod", (void*)strtod_hook_func, NULL));
  plthook_close(plthook);
}

int main(int argc, char **argv) {
  double expected_result = strtod("3.7", NULL);
  enum open_mode open_mode;

  if (argc != 2) {
    show_usage(argv[0]);
    exit(1);
  }

  if (strcmp(argv[1], "open") == 0) {
    open_mode = OPEN_MODE_DEFAULT;
  } else if (strcmp(argv[1], "open_by_handle") == 0) {
    open_mode = OPEN_MODE_BY_HANDLE;
  } else if (strcmp(argv[1], "open_by_address") == 0) {
    open_mode = OPEN_MODE_BY_ADDRESS;
  } else {
    show_usage(argv[0]);
    exit(1);
  }

  /* resolve the function addresses by lazy binding. */
  strtod_cdecl("3.7", NULL);
  hook_function_calls_in_executable(open_mode);
  hook_function_calls_in_library(open_mode);
  CHK_RESULT(strtod_cdecl, "3.7", expected_result);
  printf("success\n");
  return 0;
}