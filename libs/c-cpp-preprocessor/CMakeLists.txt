add_library(c-cpp-preprocessor
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/preprocessor.cpp
)

target_include_directories(c-cpp-preprocessor PRIVATE include)
target_compile_options(c-cpp-preprocessor PRIVATE -Wall -Werror)