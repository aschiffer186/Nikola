# Create library for Lexer
add_library(NikolaLexer STATIC 
            lex.yy.cc)
target_include_directories(NikolaLexer PUBLIC include)
target_compile_options(NikolaLexer PRIVATE ${CXX_COMPILE_OPTIONS})

set(NIKOLA_LEXER_SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(NIKOLA_LEXER_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)