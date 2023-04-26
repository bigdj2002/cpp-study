add_library(cpp-exception
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cexception.cpp
)

target_include_directories(cpp-exception PRIVATE include)
target_compile_options(cpp-exception PRIVATE -Wall -Werror)