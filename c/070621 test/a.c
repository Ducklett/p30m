#ifndef TEST_ENTRYPOINT
#define TEST_ENTRYPOINT testAdd
#endif

#include "./test.h"

int add(int a, int b) { return a + b; }

void testAdd()
{
	test_section("Addtition");
	test_equal("1 + 1 = 2", add(1, 1), 2);
	test_equal("10 + 21 = 31", add(10, 21), 31);
}
