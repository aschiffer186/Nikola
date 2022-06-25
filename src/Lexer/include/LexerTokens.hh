#ifndef LEXER_TOKENS_HH
#define LEXER_TOKENS_HH

#include <array>
#include <ostream>
#include <string>


namespace Nikola::FrontEnd::Lexer
{
    enum class NikolaTokenKind
    {
        NikolaEOF,
        NikolaError,
        NikolaIntegerLiteral,
        NikolaRealLiteral,
        NikolaComplexLiteral,
        NikolaStringLiteral,
        NikolaCharLiteral,
        NikolaIdentifier
    };

    inline const std::array<std::string, 8> tokenKindNames = {
        "EOF",
        "Error", 
        "Integer Literal",
        "Real Literal",
        "Complex Literal",
        "String Literal",
        "Character Literal",
        "Identifier"
    };

    struct NikolaToken
    {
        int line;
        int startCol;
        int endCol;
        NikolaTokenKind kind;
        std::string value;
    };

    std::ostream& operator<<(std::ostream& os, const NikolaToken& tok);
} // namespace Nikola::FrontEnd::Lexer



#endif