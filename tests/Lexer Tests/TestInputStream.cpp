#include <fstream>

#include <gtest/gtest.h>

#include "InputStream.hh"

namespace NIS = Nikola::FrontEnd::Lexer::_detail;

TEST(TestLexer, TestBasicIteration)
{
    std::string test ="abcdefg";
    std::istringstream ssin{test};

    NIS::InputStream is{ssin};

    for(size_t i = 0; i < test.length(); ++i)
    {
        EXPECT_EQ(*is, test[i]);
        EXPECT_EQ(is.getCol(), i + 1);
        EXPECT_EQ(is.getLine(), 1);
        ++is;
    }

    ++is;
    EXPECT_EQ(*is, NIS::InputStream<char>::NIKOLA_EOF);
    EXPECT_EQ(is.getCol(), test.length() + 1);
    EXPECT_EQ(is.getLine(), 1);
}

TEST(TestLexer, TestSpaceHandling) 
{
    std::string test = "a bcd   efg ";
    std::istringstream ssin{test};

    NIS::InputStream is{ssin};

    EXPECT_EQ(*is, 'a');
    EXPECT_EQ(is.getCol(), 1);
    EXPECT_EQ(is.getLine(), 1);

    ++is;
    EXPECT_EQ(*is, 'b');
    EXPECT_EQ(is.getCol(), 3);
    EXPECT_EQ(is.getLine(), 1);

    ++is;
    ++is;
    ++is;
    EXPECT_EQ(*is, 'e');
    EXPECT_EQ(is.getCol(), 9);
    EXPECT_EQ(is.getLine(), 1);

    ++is;
    ++is;
    ++is;
    EXPECT_EQ(*is, NIS::InputStream<char>::NIKOLA_EOF);
    EXPECT_EQ(is.getCol(), test.length() + 1);
    EXPECT_EQ(is.getLine(), 1);
}

TEST(TestLexer, TestLookaheadChar)
{
    std::string test = "a b";
    std::istringstream ssin{test};

    NIS::InputStream is{ssin};

    EXPECT_EQ(is.lookahead(), ' ');
    EXPECT_EQ(*is, 'a');

    ++is;
    EXPECT_EQ(is.lookahead(), NIS::InputStream<char>::NIKOLA_EOF);
    EXPECT_EQ(*is, 'b');
}

TEST(TestLexer, TestFileInput)
{
    std::ifstream fin{"C:\\Users\\aschi\\Dropbox\\Nikola\\tests\\Lexer Tests\\Input Files\\Input1.txt"};

    NIS::InputStream is{fin};

    EXPECT_EQ(is.lookahead(), 'b');
    EXPECT_EQ(*is, 'a');
    EXPECT_EQ(is.getCol(), 1);
    EXPECT_EQ(is.getLine(), 1);
    ++is;
    ++is;
    ++is;
    ++is;
    ++is;
    ++is;
    ++is;
    EXPECT_EQ(is.lookahead(), 'i');
    EXPECT_EQ(*is, 'h');
    EXPECT_EQ(is.getCol(), 1);
    EXPECT_EQ(is.getLine(), 2);
    ++is;
    EXPECT_EQ(is.lookahead(), ' ');
    EXPECT_EQ(*is, 'i');
    EXPECT_EQ(is.getCol(), 2);
    EXPECT_EQ(is.getLine(), 2);
    ++is;
    EXPECT_EQ(*is, NIS::InputStream<char>::NIKOLA_EOF);
    EXPECT_EQ(is.getCol(), 2);
    EXPECT_EQ(is.getLine(), 3);
}