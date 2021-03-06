/*
Third iteration of test framework (second was fubar)
Done in 15(!!) minutes
It supports running sections of the test suite
Each section should define TEST_ENTRYPOINT if it isn't already defined
the defined entrypoint is then called by the test framework

See main() at the bottom of this file
*/

#ifndef TEST_H
#define TEST_H

#include <stdbool.h>
#include <stdio.h>

static int test_pass;
static int test_fail;

void test_section(const char *name) { printf("#      %s\n", name); }
void test(const char *msg, bool pass)
{
	if (pass) {
		test_pass++;
		printf("\33[032m[PASS]\33[0m %s\n", msg);
	} else {
		test_fail++;
		printf("\33[031m[FAIL]\33[0m %s\n", msg);
	}
}
#define test_equal(msg, a, b) test(msg, (a) == (b))

#define TESTPLUR(n) (n == 1 ? "test" : "tests")

void TEST_ENTRYPOINT();

void main()
{
	printf("==============\n");
	TEST_ENTRYPOINT();
	printf("==============\n");
	int test_ran = test_pass + test_fail;
	printf("%d %s ran\n", test_ran, TESTPLUR(test_ran));
	if (test_pass) {

		if (test_pass == test_ran) {
			printf("\33[032mALL TESTS PASSED!\33[0m\n");
		} else {
			printf("\33[032m%d %s passed\33[0m\n", test_pass, TESTPLUR(test_pass));
		}
	}
	if (test_fail) {
		printf("\33[031m%d %s failed\33[0m\n", test_fail, TESTPLUR(test_fail));
	}
}
#endif
