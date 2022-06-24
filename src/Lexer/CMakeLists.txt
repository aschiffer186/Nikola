set(LEXER_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(LEXER_INCLUDE_DIR ${LEXER_SOURCE_DIR}/include)

add_library(Lexer INTERFACE
            "include/InputStream.hh")
target_include_directories(Lexer INTERFACE ${LEXER_INCLUDE_DIR})