add_library(cpp-template
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ctemplate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/foo.cpp
)

target_include_directories(cpp-template PRIVATE include)
target_compile_options(cpp-template PRIVATE -Wall -Werror)