/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Event loop wrapper.
 * deps: event_epoll.c event_kqueue.c.
 */

#ifndef __EVENT_H__
#define __EVENT_H__

#if defined(__cplusplus)
extern "C" {
#endif

#include <stdlib.h>

#define EVENT_MIN_RESERVED_FDS 32
#define EVENT_FDSET_INCR 96
#define EVENT_TIMER_ID_MAX 1024 * 10

#define EVENT_NONE 0b000
#define EVENT_READABLE 0b001
#define EVENT_WRITABLE 0b010
#define EVENT_ERROR 0b100

#define EVENT_LOOP_RUNNING 0
#define EVENT_LOOP_STOPPED 1

#ifdef __linux__
#define HAVE_EPOLL 1
#endif

#if defined(__APPLE__) || defined(__FreeBSD__) || defined(__NetBSD__) || \
    defined(__OpenBSD__)
#define HAVE_KQUEUE 1
#endif

#ifdef __sun
#include <sys/feature_tests.h>
#ifdef _dtrace_version
#define HAVE_EVPORT 1
#endif
#endif

#define event_loop(size) event_loop_new(size)
#define event_add_in(loop, fd, cb, data) \
    event_add(loop, fd, EVENT_READABLE, cb, data);
#define event_add_out(loop, fd, cb, data) \
    event_add(loop, fd, EVENT_WRITABLE, cb, data);
#define event_del_in(loop, fd) event_del(loop, fd, EVENT_READABLE);
#define event_del_out(loop, fd) event_del(loop, fd, EVENT_WRITABLE);

enum {
    EVENT_OK = 0,        /* operation is ok */
    EVENT_ENOMEM = 1,    /* no memory error */
    EVENT_EFAILED = 2,   /* operation is failed */
    EVENT_ERANGE = 3,    /* range is invalid */
    EVENT_ENOTFOUND = 4, /* not found error */
};

struct event_loop;
struct event_api;

typedef void (*event_cb_t)(struct event_loop *loop, int fd, int mask,
                           void *data);
typedef void (*event_timer_cb_t)(struct event_loop *loop, int id, void *data);

struct event {
    int mask;       /* EVENT_(NONE|READABLE|WRITABLE..) */
    event_cb_t rcb; /* callback function on EVENT_READABLE */
    event_cb_t wcb; /* callback function on EVENT_WRITABLE */
    event_cb_t ecb; /* callback function on EVENT_ERROR */
    void *data;     /* user defined data */
};

struct event_timer {
    int id;              /* timer identifier [0, EVENT_TIMER_ID_MAX) */
    event_timer_cb_t cb; /* callback function on timer fired */
    long interval;       /* periodicity interval to fire (ms) */
    long fire_at;        /* the time for the next fire (ms) */
    void *data;          /* user defined data */
};

struct event_timer_heap {
    struct event_timer *timers[EVENT_TIMER_ID_MAX];
    size_t len;
};

struct event_loop {
    int size;              /* the max number of fds to track */
    int state;             /* one of EVENT_LOOP_(STOPPED|RUNNING) */
    int num_timers;        /* the number of timers */
    struct event *events;  /* struct event[] */
    struct event_api *api; /* to be implemented */
    struct event_timer
        timers[EVENT_TIMER_ID_MAX]; /* struct event_timers[MAX] */
    struct event_timer_heap *timer_heap;
};

struct event_loop *event_loop_new(int size);
void event_loop_free(struct event_loop *loop);
int event_loop_start(struct event_loop *loop);
void event_loop_stop(struct event_loop *loop);
int event_add(struct event_loop *loop, int fd, int mask, event_cb_t cb,
              void *data); /* O(1) */
int event_del(struct event_loop *loop, int fd, int mask);
int event_wait(struct event_loop *loop);
int event_add_timer(struct event_loop *loop, long interval, event_timer_cb_t cb,
                    void *data); /* O(EVENT_TIMER_ID_MAX) */
int event_del_timer(struct event_loop *loop, int id); /* O(1) */

#if defined(__cplusplus)
}
#endif

#endif
