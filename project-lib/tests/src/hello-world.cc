
#include <gtest/gtest.h>

#include "hello-world.hh"

TEST(PROJECT_LIB,HELLO_WORLD)
{
    EXPECT_EQ(GetHelloWorld(),"Hello, World!");
}
