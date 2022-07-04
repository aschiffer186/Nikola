#ifndef NIKOLA_LEXER_HH
#define NIKOLA_LEXER_HH

#include <string>

#include "InputStream.hh"
#include "LexerTokens.hh"

namespace Nikola::FrontEnd::Lexer
{
    class NikolaLexer
    {
    public:
        explicit NikolaLexer(const std::istream& in);

        NikolaToken nextToken();

        NikolaToken lookahead();
    private:
       _detail::InputStream M_input_stream;
    private:
        enum StateMachineState 
        {
            ERROR,
            START,
            DIGIT,
            INTEGER_SUFFIX,
            LONG_LONG_INTEGER_SUFFIX,
            UNIT_SUFFIX_BEGIN,
            UNIT_SUFFIX_UNIT,
            UNIT_SUFFIX_EXPONENT,
            UNIT_SUFFIX_NEGATIVE_EXPONENT,
            PERIOD,
            REAL_LITERAL,
            REAL_LITERAL_EXPONENT_BEGIN,
            REAL_LITERAL_EXPONENT
        };

        enum class NumericLiteralType
        {
            INTEGER,
            REAL,
            COMPLEX
        };
    }; 
} // namespace Nikola::FrontEnd::Lexer


#endif