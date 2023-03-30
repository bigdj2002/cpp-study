add_library(cpp-inheritance
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cinheritance.cpp
)

target_include_directories(cpp-inheritance PRIVATE include)
target_compile_options(cpp-inheritance PRIVATE -Wall -Werror)