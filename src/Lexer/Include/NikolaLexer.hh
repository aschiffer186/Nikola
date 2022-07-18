#ifndef NIKOLA_LEXER_HH
#define NIKOLA_LEXER_HH

#include "LexerTokens.hh"

#if !defined(yyFlexLexerOnce)
#include <FlexLexer.h>
#endif 

namespace Nikola::FrontEnd::Lexer
{
    class NikolaLexer : yyFlexLexer
    {
        explicit NikolaLexer(std::istream& in);

        using FlexLexer::yylex;

        virtual NikolaToken nexToken();
    private:
        NikolaToken makeToken(NikolaTokenKind kind) const;
    private:
        size_t col;
        size_t line;
    };
}

#endif