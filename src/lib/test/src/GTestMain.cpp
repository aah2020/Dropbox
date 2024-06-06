#include <stdio.h>
#include "gtest/gtest.h"
#include <string>
#include <iostream>
#include <iostream>

// Main function for GTest
GTEST_API_ int main(int argc, char **argv)
{
    printf("Running main() from gtest_main.cc\n");
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

