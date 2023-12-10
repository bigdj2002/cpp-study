add_library(leet STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/q_0001.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/q_0002.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/q_0945.cpp
)

target_include_directories(leet PRIVATE include)
target_compile_options(leet PRIVATE -Wall -Werror)