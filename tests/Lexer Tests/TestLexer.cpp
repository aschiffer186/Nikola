#include <sstream>

#include <gtest/gtest.h>

TEST(TestLexer, TestLexIntegerLiteral1)
{
    std::string test = "1234";
    std::istringstream ssin{test};
}