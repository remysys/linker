/**
 * Copyright (c) 2015, Chao Wang <hit9@icloud.com>
 */

#ifdef __linux
#include <mcheck.h>
#endif

#include "test.h"

/**
 * buf_test
 */
void case_buf_clear();
void case_buf_put();
void case_buf_puts();
void case_buf_putc();
void case_buf_str();
void case_buf_isempty();
void case_buf_sprintf();
void case_buf_lrm();
void case_buf_len();
void case_buf_cap();
static struct test_case buf_test_cases[] = {
    {"buf_clear", &case_buf_clear},
    {"buf_put", &case_buf_put},
    {"buf_puts", &case_buf_puts},
    {"buf_putc", &case_buf_putc},
    {"buf_str", &case_buf_str},
    {"buf_isempty", &case_buf_isempty},
    {"buf_sprintf", &case_buf_sprintf},
    {"buf_lrm", &case_buf_lrm},
    {"buf_len", &case_buf_len},
    {"buf_cap", &case_buf_cap},
    {NULL, NULL},
};

/**
 * cfg_test
 */
void case_cfg_get();
static struct test_case cfg_test_cases[] = {
    {"cfg_get", &case_cfg_get}, {NULL, NULL},
};

/**
 * datetime_test
 */
void case_datetime_stamp_now();
static struct test_case datetime_test_cases[] = {
    {"datetime_stamp_now", &case_datetime_stamp_now}, {NULL, NULL},
};

/**
 * dict_test
 */
void case_dict_set();
void case_dict_get();
void case_dict_pop();
void case_dict_has();
void case_dict_clear();
void case_dict_resize();
void case_dict_iter();
static struct test_case dict_test_cases[] = {
    {"dict_set", &case_dict_set},
    {"dict_get", &case_dict_get},
    {"dict_pop", &case_dict_pop},
    {"dict_has", &case_dict_has},
    {"dict_clear", &case_dict_clear},
    {"dict_resize", &case_dict_resize},
    {"dict_iter", &case_dict_iter},
    {NULL, NULL},
};

/**
 * event_test
 */
void case_event_simple();
static struct test_case event_test_cases[] = {
    {"event_simple", &case_event_simple}, {NULL, NULL},
};

/**
 * heap_test
 */
void case_heap_clear();
void case_heap_len();
void case_heap_cap();
void case_heap_push();
void case_heap_pop();
void case_heap_top();
void case_heap_pushpop();
void case_heap_del();
void case_heap_repalce();
static struct test_case heap_test_cases[] = {
    {"heap_clear", &case_heap_clear},
    {"heap_len", &case_heap_len},
    {"heap_cap", &case_heap_cap},
    {"heap_push", &case_heap_push},
    {"heap_pop", &case_heap_pop},
    {"heap_top", &case_heap_top},
    {"heap_pushpop", &case_heap_pushpop},
    {"heap_del", &case_heap_del},
    {"heap_replace", &case_heap_repalce},
    {NULL, NULL},
};

/**
 * ketama_test
 */
void case_ketama_balance();
void case_ketama_consistence();
static struct test_case ketama_test_cases[] = {
    {"ketama_balance", &case_ketama_balance},
    {"ketama_consistence", &case_ketama_consistence},
    {NULL, NULL},
};

/**
 * list_test
 */
void case_list_clear();
void case_list_lpush();
void case_list_rpush();
void case_list_lpop();
void case_list_rpop();
void case_list_iter();
static struct test_case list_test_cases[] = {
    {"list_clear", &case_list_clear},
    {"list_lpush", &case_list_lpush},
    {"list_rpush", &case_list_rpush},
    {"list_lpop", &case_list_lpop},
    {"list_rpop", &case_list_rpop},
    {"list_iter", &case_list_iter},
    {NULL, NULL},
};

/**
 * log_test
 */
void case_log_open_close();
void case_log_log();
void case_log_rotate();
static struct test_case log_test_cases[] = {
    {"log_open_close", &case_log_open_close},
    {"log_log", &case_log_log},
    {"log_rotate", &case_log_rotate},
    {NULL, NULL},
};

/**
 * map_test
 */
void case_map_set();
void case_map_get();
void case_map_pop();
void case_map_has();
void case_map_clear();
void case_map_iter();
static struct test_case map_test_cases[] = {
    {"map_set", &case_map_set},
    {"map_get", &case_map_get},
    {"map_pop", &case_map_pop},
    {"map_has", &case_map_has},
    {"map_clear", &case_map_clear},
    {"map_iter", &case_map_iter},
    {NULL, NULL},
};

/**
 * queue_test
 */
void case_queue_clear();
void case_queue_push_pop_top();
static struct test_case queue_test_cases[] = {
    {"queue_clear", &case_queue_clear},
    {"queue_push_pop_top", &case_queue_push_pop_top},
    {NULL, NULL},
};

/**
 * skiplist_test
 */
void case_skiplist_base();
void case_skiplist_push();
void case_skiplist_pop();
void case_skiplist_popfirst();
void case_skiplist_poplast();
void case_skiplist_get();
static struct test_case skiplist_test_cases[] = {
    {"skiplist_base", &case_skiplist_base},
    {"skiplist_push", &case_skiplist_push},
    {"skiplist_pop", &case_skiplist_pop},
    {"skiplist_popfirst", &case_skiplist_popfirst},
    {"skiplist_poplast", &case_skiplist_poplast},
    {"skiplist_get", &case_skiplist_get},
    {NULL, NULL},
};

/**
 * stack_test
 */
void case_stack_clear();
void case_stack_push();
void case_stack_pop();
void case_stack_top();
static struct test_case stack_test_cases[] = {
    {"stack_clear", &case_stack_clear},
    {"stack_push", &case_stack_push},
    {"stack_pop", &case_stack_pop},
    {"stack_top", &case_stack_top},
    {NULL, NULL},
};

/**
 * strings_test
 */
void case_strings_search();
void case_strings_rand();
void case_strings_replace();
static struct test_case strings_test_cases[] = {
    {"strings_search", &case_strings_search},
    {"strings_rand", &case_strings_rand},
    {"strings_replace", &case_strings_replace},
    {NULL, NULL},
};

/**
 * utils_test
 */
void case_utils_min();
void case_utils_max();
static struct test_case utils_test_cases[] = {
    {"utils_min", &case_utils_min},
    {"utils_max", &case_utils_max},
    {NULL, NULL},
};

static void run_cases(const char *name, struct test_case cases[]) {
    int idx = 0;

    while (1) {
        struct test_case c = cases[idx];
        if (c.name == NULL || c.fn == NULL) break;
        double start_at = datetime_stamp_now();
        (c.fn)();
        double end_at = datetime_stamp_now();
        idx += 1;
        fprintf(stderr, "ok\t%-27s %-27s %17.3fµs\n", name, c.name,
                1000.0 * (end_at - start_at));
    }
}

int main(int argc, const char *argv[]) {
#ifdef __linux
    mtrace();
#endif
    run_cases("buf_test", buf_test_cases);
    run_cases("cfg_test", cfg_test_cases);
    run_cases("datetime_test", datetime_test_cases);
    run_cases("dict_test", dict_test_cases);
    run_cases("event_test", event_test_cases);
    run_cases("heap_test", heap_test_cases);
    run_cases("ketama_test", ketama_test_cases);
    run_cases("list_test", list_test_cases);
    run_cases("log_test", log_test_cases);
    run_cases("map_test", map_test_cases);
    run_cases("queue_test", queue_test_cases);
    run_cases("skiplist_test", skiplist_test_cases);
    run_cases("stack_test", stack_test_cases);
    run_cases("strings_test", strings_test_cases);
    run_cases("utils_test", utils_test_cases);
    return 0;
}
