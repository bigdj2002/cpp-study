add_library(cpp-pointer
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cpointer.cpp
)

target_include_directories(cpp-pointer PRIVATE include)
target_compile_options(cpp-pointer PRIVATE -Wall -Werror)