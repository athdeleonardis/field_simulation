#include <stdio.h>
#include <stdlib.h>
#include "test.h"

void test_log_success(test_t *test) {
    printf("TEST %16s -- SUCCESS\n", test->name);
    exit(0);
}

void test_log_failure(test_t *test, const char *message) {
    printf("TEST %16s -- FAILURE -- %s\n", test->name, message);
    exit(0);
}
void test_assert_equal_int(test_t *test, int a, int b, const char *message) {
    if (a == b)
        return;
    test_log_failure(test, message);
}
