#ifndef TEST
#define TEST

typedef struct test {
    char name[16];
} test_t;

void test_log_success(test_t *test);
void test_log_failure(test_t *test, const char *message);
void test_assert_equal_int(test_t *test, int a, int b, const char *message);

#endif