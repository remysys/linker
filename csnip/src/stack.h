/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Array based stack implementation.
 * deps: None.
 */

#ifndef __STACK_H__
#define __STACK_H__

#include <stdlib.h>

#if defined(__cplusplus)
extern "C" {
#endif

/* note that real allocated size is cap * sizeof(void *). */
#define STACK_CAP_MAX 16 * 1024 * 1024 /* max stack capacity: 16mb */
#define STACK_UNIT_MIN 1               /* min stack realloc unit: 1 */
#define STACK_UNIT_MAX 1024            /* max stack realloc unit: 1k */

#define stack(cap) stack_new(cap)

enum {
    STACK_OK = 0,     /* operation is ok */
    STACK_ENOMEM = 1, /* no memory error */
};

struct stack {
    size_t len;  /* stack length */
    size_t cap;  /* stack capacity */
    void **data; /* stack data */
};

struct stack *stack_new(size_t cap);
void stack_free(struct stack *stack);
void stack_clear(struct stack *stack);
size_t stack_len(struct stack *stack);           /* O(1) */
size_t stack_cap(struct stack *stack);           /* O(1) */
void *stack_pop(struct stack *stack);            /* O(1) */
void *stack_top(struct stack *stack);            /* O(1) */
int stack_push(struct stack *stack, void *data); /* O(1) */
int stack_grow(struct stack *stack, size_t cap);

#if defined(__cplusplus)
}
#endif

#endif
