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
        enum State_Machine_State 
        {
            ERROR,
            START,
            DIGIT,
            INTEGER_SUFFIX,
            LONG_LONG_INTEGER_SUFFIX,
            UNIT_SUFFIX_BEGIN,
            UNIT_SUFFIX
        };
    }; 
} // namespace Nikola::FrontEnd::Lexer


#endif