#include "LexerTokens.hh"

namespace Nikola::FrontEnd::Lexer 
{
    std::ostream& operator<<(std::ostream& os, const NikolaToken& tok)
    {
        os << "{Token Kind: " << tokenKindNames[static_cast<int>(tok.kind)];
        if (static_cast<int>(tok.kind) > 1 && static_cast<int>(tok.kind) < 8)
            os << ", Token Value: " << tok.value;
        os << ", Line: " << tok.line; 
        os << ", Start Column: " << tok.startCol << ", End Column: " << tok.endCol;
        os << "}";
        return os;
    }
}