add_library(cpp-thread
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cthread.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cthread_sync.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cthread_async.cpp
)

target_include_directories(cpp-thread PRIVATE include)
target_compile_options(cpp-thread PRIVATE -Wall -Werror)