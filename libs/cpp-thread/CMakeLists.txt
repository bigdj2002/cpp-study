add_library(cpp-thread
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cthread_1.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cthread_2.cpp
)

target_include_directories(cpp-thread PRIVATE include)
target_compile_options(cpp-thread PRIVATE -Wall -Werror)