#ifndef TEST_ENTRYPOINT
#define TEST_ENTRYPOINT testSuite
#endif

#include "./test.h"
#include "./a.c"
#include "./b.c"

void testSuite()
{
    testAdd();
    testSub();
}
