#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test.h"

void test_initialize(test_t *test, int argc, char *argv[]) {
    test->do_log = 0;
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "do_log") == 0) {
            test->do_log = 1;
        }
    }
}

void test_log_success(test_t *test) {
    printf("TEST %16s -- SUCCESS\n", test->name);
    exit(0);
}

void test_log_failure(test_t *test, const char *message) {
    printf("TEST %16s -- FAILURE -- %s\n", test->name, message);
    exit(0);
}

void test_assert_equal_int(test_t *test, uint32_t a, uint32_t b, const char *message) {
    if (a == b)
        return;
    test_log_failure(test, message);
}
