#ifndef TEST_ENTRYPOINT
#define TEST_ENTRYPOINT testSub
#endif

#include "./test.h"

int sub(int a, int b) { return a - b; }

void testSub()
{
	test_section("Subtraction");
	test_equal("1 - 1 = 0", sub(1, 1), 0);
	test_equal("10 - 21 = -11", sub(10, 21), -11);
}
