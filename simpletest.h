#if !defined(__SIMPLETEST_H)
#define __SIMPLETEST_H

#include <stdio.h>

// Color
#define NORMAL "\033[m"
#define RED "\033[0;32;31m"
#define LIGHT_RED "\033[1;31m"
#define GREEN "\033[0;32;32m"
#define LIGHT_GREEN "\033[1;32m"
#define BLUE "\033[0;32;34m"
#define LIGHT_BLUE "\033[1;34m"
#define DARY_GRAY "\033[1;30m"
#define CYAN "\033[0;36m"
#define LIGHT_CYAN "\033[1;33m"
#define LIGHT_GRAY "\033[0;37m"
#define WHITE "\033[1;37m"

static unsigned int test_number = 0;
static unsigned int test_fail = 0;

#define test_this(des, exp)                     \
    do {                                        \
        test_number++;                          \
        printf("%u -- %s: ", test_number, des); \
        if (exp)                                \
            puts(LIGHT_GREEN "PASSED" NORMAL);  \
        else {                                  \
            puts(RED "FAILED" NORMAL);          \
            test_fail++;                        \
        }                                       \
    } while (0)

static inline void test_report(void)
{
    printf("%u tests. %u passed, %u failed\n", test_number,
           test_number - test_fail, test_fail);
    if (test_fail) {
        puts(LIGHT_RED "=====WARNING=====\n" NORMAL "We got failed test.");
    }
}
#endif