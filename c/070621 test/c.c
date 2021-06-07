#ifndef TEST_ENTRYPOINT
#define TEST_ENTRYPOINT testSuite
#endif

#include "./a.c"
#include "./b.c"
#include "./test.h"

void testSuite()
{
	testAdd();
	testSub();
}
