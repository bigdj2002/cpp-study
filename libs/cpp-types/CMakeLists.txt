add_library(cpp-types
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ctypes.cpp
)

target_include_directories(cpp-types PRIVATE include)
target_compile_options(cpp-types PRIVATE -Wall -Werror)