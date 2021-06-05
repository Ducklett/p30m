#include "./cest.h"

int add(int a, int b)
{
    return a + b;
}

int sub(int a, int b)
{
    return a - b;
}

void main()
{
    test_start();

    test_section("Adding");
    test_equal("10 + 20 = 30", add(10, 20), 30);
    test_equal("1 + 1 = 2", add(1, 1), 2);

    test_section("Subtracting");
    test_equal("10 - 20 = -1", sub(10, 20), -10);
    test_equal("1 - 1 = 0", sub(1, 1), 0);

    test_end();
}
