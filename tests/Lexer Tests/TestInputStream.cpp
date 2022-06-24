#include <gtest/gtest.h>

#include "InputStream.hh"

namespace NIS = Nikola::FrontEnd::Lexer::_detail;

TEST(TestLexer, Test1)
{
    std::string test ="abcdefg";
    std::istringstream ssin{test};

    NIS::InputStream is{ssin};

    EXPECT_EQ(*is, 'a');
    EXPECT_EQ(is.getCol(), 1);
    EXPECT_EQ(is.getLine(), 1);
}