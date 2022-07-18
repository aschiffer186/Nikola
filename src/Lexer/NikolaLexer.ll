%option c++ noyywrap nodefault
%option yyclass="Nikola::FrontEnd::Lexer::NikolaLexer"

%{
    #include <istream>

    #include "NikolaLexer.hh"

    using TokenType = Nikola::FrontEnd::Lexer::NikolaToken;
    using TokenKindType = Nikola::FrontEnd::Lexer::NikolaTokenKind;

    #undef YY_DECL
    #define YY_DECL TokenType Nikola::FrontEnd::Lexer::NikolaLexer::nextToken();

    #define yyterminate() return {TokenKindType::EOF;}
%}

digit [0-9]
unit_suffix_unit _[[:alpha]]+(_?[[:digit:]]+)?
unit_suffix {unit_suffix_unit}+
char [a-zA-Z]
escape_char \[a-zA-Z]

%%
{digit}+{unit_suffix}? {return makeToken(TokenKindType::NikolaIntegerLiteral);}
{digit}*\.{digit}+([eE][+-]{digit}+)?{unit_suffix}? {return makeToken(TokenKindType::NikolaRealLiteral);}
{digit}*\.{digit}+([eE][+-]{digit}+)?i{unit_suffix}? {return makeToken(TokenKindType::NikolaComplexLiteral);}
'{char}|{escape_char}' {return makeToken(TokenKindType::NiokolaCharLiteral);}
\"({char}|{escape_char})*\" {return makeToken(TokenKindType::NikolaStringLiteral);}

%%
TokenType Nikola::FrontEnd::Lexer::makeToken(TokenKindType type)
{
    std::string text{yytext};
    return TokenType{col - txt.length(), col, line, type, text};
}