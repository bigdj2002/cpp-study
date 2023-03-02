add_library(cpp-lamda
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/clamda.cpp
)

target_include_directories(cpp-lamda PRIVATE include)
target_compile_options(cpp-lamda PRIVATE -Wall -Werror)