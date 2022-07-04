set(LEXER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LEXER_INCLUDE_DIR ${LEXER_SOURCE_DIR}/include)

add_library(Lexer
            "include/InputStream.hh"
            "include/LexerTokens.hh"
            "include/NikolaLexer.hh"
            "InputStream.cpp"
            "LexerTokens.cpp"
            "NikolaLexer.cpp")
target_include_directories(Lexer PUBLIC ${LEXER_INCLUDE_DIR})
target_compile_options(Lexer PRIVATE "-g")