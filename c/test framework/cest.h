/*
A basic unit testing framework
Start testing with test_start
You can check if a condition is met with test(msg,passed)
You can assert equality with test_equal(msg, a, b)
End testing with test_end
The the number of tests that pass and fail will be counted and displayed at the end 

You're intended to run your test suite with tcc -run tests.c
This way no compilation step is required
*/

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>

#define COLGREEN "\033[0;32m"
#define COLRED "\033[0;31m"
#define COLRESET "\033[0m"
#define TESTPLURAL(p) (p == 1 ? "test" : "tests")

static int test_num_passed = 0;
static int test_num_failed = 0;
void test_start()
{
    test_num_passed = 0;
    test_num_failed = 0;
    printf("======\n");
}

void test_end()
{
    int num_tests = test_num_passed + test_num_failed;
    printf("======\n");
    printf("%d tests ran\n", num_tests);

    if (test_num_passed == num_tests)
    {
        printf("%sALL TESTS PASSED!%s\n", COLGREEN, COLRESET);
        return;
    }

    if (test_num_passed)
        printf("%s%d %s passed %s\n", COLGREEN, test_num_passed, TESTPLURAL(test_num_passed), COLRESET);
    if (test_num_failed)
        printf("%s%d %s failed %s\n", COLRED, test_num_failed, TESTPLURAL(test_num_failed), COLRESET);
}

void test(const char *msg, bool passed)
{
    if (passed)
    {
        test_num_passed++;
        printf("%s[%s]%s %s\n", COLGREEN, "PASS", COLRESET, msg);
    }
    else
    {
        test_num_failed++;
        printf("%s[%s]%s %s\n", COLRED, "FAIL", COLRESET, msg);
    }
}

#define test_equal(msg, a, b) test(msg, (a) == (b))
#define test_section(name) printf("#      %s:\n", (name));

#undef COLGREEN
#undef COLRED
#undef COLRESET
#undef TESTPLURAL
