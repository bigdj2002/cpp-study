add_library(cpp-memory
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cmemory.cpp
)

target_include_directories(cpp-memory PRIVATE include)
target_compile_options(cpp-memory PRIVATE -Wall -Werror)