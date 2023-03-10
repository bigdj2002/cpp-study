add_library(cpp-LRvalue
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/lrvalue.cpp
)

target_include_directories(cpp-LRvalue PRIVATE include)
target_compile_options(cpp-LRvalue PRIVATE -Wall -Werror)