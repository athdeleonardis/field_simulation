#ifndef TEST
#define TEST

#include <stdint.h>

typedef struct test {
    char name[16];
    uint32_t do_log;
} test_t;

void test_initialize(test_t *test, int argc, char *argv[]);
void test_log_success(test_t *test);
void test_log_failure(test_t *test, const char *message);
void test_assert_equal_int(test_t *test, uint32_t a, uint32_t b, const char *message);

#endif