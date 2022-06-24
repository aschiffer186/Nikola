add_executable(LexerTest TestInputStream.cpp)
target_link_libraries(LexerTest PRIVATE Lexer gtest_main)
target_compile_options(LexerTest PRIVATE ${CXX_TEST_OPTIONS})
gtest_discover_tests(LexerTest)