add_library(cpp-STLs
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cppVector.cpp
)

target_include_directories(cpp-STLs PRIVATE include)
target_compile_options(cpp-STLs PRIVATE -Wall -Werror)