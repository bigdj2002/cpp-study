add_library(cpp-STLs
  STATIC
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cvector.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/carray.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cstring.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cmap.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/clist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cstack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cqueue.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ctypes.cpp
)

target_include_directories(cpp-STLs PRIVATE include)
target_compile_options(cpp-STLs PRIVATE -Wall -Werror)