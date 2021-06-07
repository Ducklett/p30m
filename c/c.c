#ifndef TEST_ENTRYPOINT
#define TEST_ENTRYPOINT testSuite
#endif

#include "./070621 test.h"
#include "./a.c"
#include "./b.c"

void testSuite()
{
    testAdd();
    testSub();
}
