enable_testing()

#Set up Google Test
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

include(GoogleTest)

SET(CXX_TEST_OPTIONS 
    "-g"
    "-std=c++20"
    "-Wall"
    "-Werror"
    "-Wextra"
    "-Wshadow"
    "-Wswitch-enum"
    "-Wstrict-overflow=5"
    "-pedantic"
    )

add_subdirectory("Lexer Tests")
