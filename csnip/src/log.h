/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 *
 * Logging implementation.
 * deps: None.
 */

#ifndef __LOG_H__
#define __LOG_H__

#include <fcntl.h>
#include <pthread.h>
#include <stdio.h>

#if defined(__cplusplus)
extern "C" {
#endif

#define LOG_LINE_LEN_MAX 1024 * 1024  // 1mb
#define LOG_FILENAME_LEN_MAX 1024     // 1kb
#define LOG_FILE_MODE 0644
#define LOG_FILE_PERM O_WRONLY | O_APPEND | O_CREAT
#define LOG_THREAD_SAFE 1

#define LOG_DEBUG_S "DEBUG"
#define LOG_INFO_S "INFO"
#define LOG_WARN_S "WARN"
#define LOG_ERROR_S "ERROR"
#define LOG_CRITICAL_S "CRIT"

enum {
    LOG_DEBUG = 10,
    LOG_INFO = 20,
    LOG_WARN = 30,
    LOG_ERROR = 40,
    LOG_CRITICAL = 50,
};

enum {
    LOG_OK = 0,        /* operation is ok */
    LOG_EOPEN = 1,     /* failed to open file */
    LOG_EWRITE = 2,    /* failed to write to file */
    LOG_ESTAT = 3,     /* failed to stat file */
    LOG_ERENAME = 4,   /* failed to rename file */
    LOG_ELINESIZE = 5, /* log line is too large */
};

struct logger {
    char *name;           /* logger name */
    char *filename;       /* filename to log */
    size_t rotate_size;   /* rotate size, in bytes (0 for no rotation) */
    int level;            /* logging level */
    int fd;               /* fd to write */
    size_t fsize;         /* original file size + number of bytes written) */
    pthread_mutex_t lock; /* lock on logging */
};

#define log_debug(...) log_log(LOG_DEBUG, LOG_DEBUG_S, __VA_ARGS__)
#define log_info(...) log_log(LOG_INFO, LOG_INFO_S, __VA_ARGS__)
#define log_warn(...) log_log(LOG_WARN, LOG_WARN_S, __VA_ARGS__)
#define log_error(...) log_log(LOG_ERROR, LOG_ERROR_S, __VA_ARGS__)
#define log_critical(...) log_log(LOG_CRITICAL, LOG_CRITICAL_S, __VA_ARGS__)

int log_open(char *name, char *filename, size_t rotate_size);
void log_close(void);
int log_reopen(void);
void log_setlevel(int level);
int log_rotate(void);
int log_log(int level, char *levelname, const char *fmt, ...);
int log_trace(void);
int log_write(char *buf, size_t len);

#if defined(__cplusplus)
}
#endif

#endif
