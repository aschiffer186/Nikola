#include <sstream>

#include <gtest/gtest.h>

#include "NikolaLexer.hh"

using namespace Nikola::FrontEnd::Lexer;

TEST(TestLexer, TestLexIntegerLiteral1)
{
    std::string test = "1234";
    std::istringstream ssin{test};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer{ssin};
    auto tok = lexer.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 4);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234");
}

TEST(TestLexer, TestLexerInterTypeSuffixes)
{
    std::string test = "1234l";
    std::istringstream ssin{test};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer{ssin};
    auto tok = lexer.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 5);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234l");

    std::string test2 = "1234L";
    std::istringstream ssin2{test2};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer2{ssin2};
    tok = lexer2.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 5);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234L");


    std::string test3 = "1234s";
    std::istringstream ssin3{test3};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer3{ssin3};
    tok = lexer3.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 5);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234s");

    std::string test4 = "1234S";
    std::istringstream ssin4{test4};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer4{ssin4};
    tok = lexer4.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 5);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234S");

    std::string test5 = "1234b";
    std::istringstream ssin5{test5};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer5{ssin5};
    tok = lexer5.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 5);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234b");

    std::string test6 = "1234B";
    std::istringstream ssin6{test6};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer6{ssin6};
    tok = lexer6.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 5);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234B");

    std::string test7 = "1234LL";
    std::istringstream ssin7{test7};

    Nikola::FrontEnd::Lexer::NikolaLexer lexer7{ssin7};
    tok = lexer7.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 6);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234LL");
}

TEST(TestLexer, TestLexInputUnitSuffix)
{
    std::string test1 = "1234_m";
    std::istringstream ssin1{test1};

    NikolaLexer lexer1{ssin1};
    auto tok = lexer1.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 6);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234_m");

    std::string test2 = "1234_km2";
    std::istringstream ssin2{test2};
    
    NikolaLexer lexer2{ssin2};
    tok = lexer2.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 8);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234_km2");

    std::string test3 = "1234_km2_s";
    std::istringstream ssin3{test3};
    
    NikolaLexer lexer3{ssin3};
    tok = lexer3.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 10);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234_km2_s");

    std::string test4 = "1234_km_2_kg";
    std::istringstream ssin4{test4};
    
    NikolaLexer lexer4{ssin4};
    tok = lexer4.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 12);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234_km_2_kg");

    std::string test5 = "1234LL_km_2_kg3";
    std::istringstream ssin5{test5};
    
    NikolaLexer lexer5{ssin5};
    tok = lexer5.nextToken();

    EXPECT_EQ(tok.startCol, 1);
    EXPECT_EQ(tok.endCol, 15);
    EXPECT_EQ(tok.line, 1);
    EXPECT_EQ(tok.kind, NikolaTokenKind::NikolaIntegerLiteral);
    EXPECT_STREQ(tok.value.c_str(), "1234LL_km_2_kg3");
}