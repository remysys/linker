UNAME_S := $(shell uname -s)

CFLAGS_SHARED = -shared -fPIC
CFLAGS = $(CFLAGS_WARNING) $(EXTRA_CFLAGS) $(OPT_CFLAGS)
CFLAGS_WARNING = -Wall
EXEEXT =
LIBS = -ldl -lm
PLTHOOK_C = plthook_elf.c
TESTS = run_tests

ifeq ($(UNAME_S),Linux)
  # Linux
  TESTS = relro_pie_tests
endif


all: libtest.so testprog

libtest.so: libtest.c libtest.h
	$(CC) $(CFLAGS_SHARED) $(CFLAGS) -DLIBTEST_DLL -o libtest.so libtest.c -lm

testprog: testprog.c ../$(PLTHOOK_C) libtest.h
	$(CC) $(CFLAGS_EXE) $(CFLAGS) -o testprog -I.. testprog.c ../$(PLTHOOK_C) -L. -ltest $(LIBS)

run_tests: clean libtest.so testprog
	LD_LIBRARY_PATH=. ./testprog open
	LD_LIBRARY_PATH=. ./testprog open_by_handle
	test "$(SKIP_OPEN_BY_ADDRESS_TEST)" || env LD_LIBRARY_PATH=. ./testprog open_by_address

check: $(TESTS)

relro_pie_tests:
	@echo ------------ check ------------
	$(MAKE) run_tests "EXTRA_CFLAGS="
	@echo ------------ check Partial RELRO ------------
	$(MAKE) run_tests "EXTRA_CFLAGS=-Wl,-z,relro"
	@echo ------------ check Full RELRO ------------
	$(MAKE) run_tests "EXTRA_CFLAGS=-Wl,-z,relro,-z,now"
	@echo ------------ check PIE ------------
	$(MAKE) run_tests "CFLAGS_EXE=-fPIE -pie"
	@echo ------------ check PIE Partial RELRO ------------
	$(MAKE) run_tests "CFLAGS_EXE=-fPIE -pie" "EXTRA_CFLAGS=-Wl,-z,relro"
	@echo ------------ check PIE Full RELRO ------------
	$(MAKE) run_tests "CFLAGS_EXE=-fPIE -pie" "EXTRA_CFLAGS=-Wl,-z,relro,-z,now"
	@echo ------------ check Partial RELRO + -fno-plt ------------
	@touch dummy.c
	@if $(CC) -c dummy.c -fno-plt; then \
	  $(MAKE) run_tests "EXTRA_CFLAGS=-Wl,-z,relro -fno-plt"; \
	else \
	  echo "skip: -fno-plt isn't supported"; \
	fi

clean:
	$(RM) libtest.so testprog