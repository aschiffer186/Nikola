#ifndef LEXER_TOKENS_HH
#define LEXER_TOKENS_HH

#include <iosfwd>
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
       NikolaCharacterLiteral,
       NikolaIdentifier 
    };

    struct NikolaToken
    {
        size_t startCol;
        size_t endCol;
        size_t line;
        NikolaTokenKind kind;
        std::string value;

        NikolaToken(size_t sc, size_t ec, size_t, NikolaTokenKind k, const std::string& value);
    };

    std::ostream& operator<<(std::ostream& os, const NikolaToken& tok);
}

#endif