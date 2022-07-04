#include "NikolaLexer.hh"

#define TRANSITION(newState) \
    {\
        state = newState;\
        ++M_input_stream;\
        tokenValue += c;\
    }

#define ACCEPT(tokenKind)\
    do\
    {\
    tokenValue += c;\
    NikolaToken token{.startCol = M_input_stream.getCol() - tokenValue.length() + 1,\
                                    .endCol = M_input_stream.getCol(),\
                                    .line = M_input_stream.getLine(),\
                                    .kind = tokenKind,\
                                    .value = tokenValue};\
                ++M_input_stream;\
                return token;\
    }\
    while(false)

namespace Nikola::FrontEnd::Lexer
{
    NikolaLexer::NikolaLexer(const std::istream& in)
    : M_input_stream{in}
    {

    }

    NikolaToken NikolaLexer::nextToken()
    {
        int state = START;
        std::string tokenValue;
        char c;
        NumericLiteralType literalType;

        while(true)
        {
            c = *M_input_stream;
            if (state == START && c == _detail::InputStream::NIKOLA_EOF)
            {
                return NikolaToken{.startCol = M_input_stream.getCol(), 
                                   .endCol = M_input_stream.getCol(),
                                   .line = M_input_stream.getLine(),
                                   .kind = NikolaTokenKind::NikolaEOF};
            }

            switch(state)
            {
                case START:
                {
                    if(isdigit(c))
                    {
                        TRANSITION(DIGIT);
                    } 
                    else if (c == '.')
                    {
                        TRANSITION(PERIOD)
                    }
                    else if (c == '\'') 
                    {

                    }
                    else if (c == '"')
                    {

                    }
                }
                break;
                case DIGIT:
                {
                    char lookahead = M_input_stream.lookahead();

                    if (isdigit(lookahead))
                    {
                        literalType = NumericLiteralType::INTEGER;
                        TRANSITION(DIGIT);
                    }
                    else if (isalpha(lookahead))
                    {
                        TRANSITION(INTEGER_SUFFIX);
                    }
                    else if (lookahead == '_')
                    {
                        TRANSITION(UNIT_SUFFIX_BEGIN);
                    }
                    else if (lookahead == '.')
                    {
                        TRANSITION(PERIOD);
                    }
                    else 
                    {
                        ACCEPT(NikolaTokenKind::NikolaIntegerLiteral);
                    }
                }
                break;
                case INTEGER_SUFFIX:
                {
                    char curr = tolower(c);
                    if (curr != 'l' && curr != 's' && curr != 'b' && curr != 'f')
                    {
                        TRANSITION(ERROR);
                    }

                    char lookahead = tolower(M_input_stream.lookahead());
                    if (lookahead == 'l')
                    {
                        TRANSITION(LONG_LONG_INTEGER_SUFFIX);
                    }
                    else if (lookahead == '_')
                    {
                        TRANSITION(UNIT_SUFFIX_BEGIN);
                    }
                    else 
                    {
                        ACCEPT(NikolaTokenKind::NikolaIntegerLiteral);
                    }
                }
                break;
                case LONG_LONG_INTEGER_SUFFIX:
                {
                    char lookahead = M_input_stream.lookahead();
                    if (lookahead == '_')
                    {
                        TRANSITION(UNIT_SUFFIX_BEGIN);
                    }
                    else 
                    {
                        ACCEPT(NikolaTokenKind::NikolaIntegerLiteral);
                    }
                }
                break;
                case PERIOD:
                {
                    char lookahead = tolower(M_input_stream.lookahead());
                    if (isdigit(lookahead))
                    {
                        TRANSITION(REAL_LITERAL);
                        literalType = NumericLiteralType::REAL;
                    }
                }
                break;
                case REAL_LITERAL:
                {
                    char lookahead = tolower(M_input_stream.lookahead());
                    if (isdigit(lookahead))
                    {
                        TRANSITION(REAL_LITERAL);
                    }
                    else if (lookahead == '_')
                    {
                        TRANSITION(UNIT_SUFFIX_BEGIN);
                    }
                    else if (lookahead == 'e')
                    {
                        TRANSITION(REAL_LITERAL_EXPONENT_BEGIN);
                    }
                    else 
                    {
                        ACCEPT(NikolaTokenKind::NikolaRealLiteral);
                    }
                }
                break;
                case UNIT_SUFFIX_BEGIN:
                {
                    char lookahead = tolower(M_input_stream.lookahead());
                    if (!isalpha(lookahead))
                    {
                        TRANSITION(ERROR);
                    }
                    TRANSITION(UNIT_SUFFIX_UNIT);
                }
                break;
                case UNIT_SUFFIX_UNIT:
                {
                    char lookahead = tolower(M_input_stream.lookahead());
                    if (isdigit(lookahead))
                    {
                        TRANSITION(UNIT_SUFFIX_EXPONENT);
                    }
                    else if (isalpha(lookahead))
                    {
                        TRANSITION(UNIT_SUFFIX_UNIT);
                    }
                    else if (lookahead == '_')
                    {
                        TRANSITION(UNIT_SUFFIX_NEGATIVE_EXPONENT);
                    }
                    else 
                    {
                        if (literalType == NumericLiteralType::INTEGER)
                        {
                            ACCEPT(NikolaTokenKind::NikolaIntegerLiteral);
                        }
                        else if (literalType == NumericLiteralType::REAL)
                        {
                            ACCEPT(NikolaTokenKind::NikolaRealLiteral);
                        }
                        else
                        {
                            ACCEPT(NikolaTokenKind::NikolaComplexLiteral);
                        }
                    }
                }
                break;
                case UNIT_SUFFIX_EXPONENT:
                {
                    char lookahead = tolower(M_input_stream.lookahead());
                    if (isdigit(lookahead))
                    {
                        TRANSITION(UNIT_SUFFIX_EXPONENT);
                    }
                    else if (lookahead == '_')
                    {
                        TRANSITION(UNIT_SUFFIX_BEGIN);
                    }
                    else 
                    {
                        if (literalType == NumericLiteralType::INTEGER)
                        {
                            ACCEPT(NikolaTokenKind::NikolaIntegerLiteral);
                        }
                        else if (literalType == NumericLiteralType::REAL)
                        {
                            ACCEPT(NikolaTokenKind::NikolaRealLiteral);
                        }
                        else
                        {
                            ACCEPT(NikolaTokenKind::NikolaComplexLiteral);
                        }
                    }
                }
                break;
                case UNIT_SUFFIX_NEGATIVE_EXPONENT:
                {
                    char lookahead = tolower(M_input_stream.lookahead());
                    if (isdigit(lookahead))
                    {
                        TRANSITION(UNIT_SUFFIX_NEGATIVE_EXPONENT);
                    }
                    else if (lookahead == '_')
                    {
                        TRANSITION(UNIT_SUFFIX_UNIT);
                    }
                    else 
                    {
                        TRANSITION(ERROR);
                    }
                }
                break;
                case ERROR:
                default:
                    break;
            }
        }
    }
}