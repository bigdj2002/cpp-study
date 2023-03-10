file(GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
  ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(program ${SRC_FILES})
target_link_libraries(program 
  PUBLIC 
    cpp-memory 
    cpp-STLs 
    c-cpp-preprocessor 
    cpp-lamda
    cpp-LRvalue
)
target_include_directories(program 
  PUBLIC 
    ${CMAKE_SOURCE_DIR}/libs/cpp-memory/include
    ${CMAKE_SOURCE_DIR}/libs/cpp-STLs/include
    ${CMAKE_SOURCE_DIR}/libs/c-cpp-preprocessor/include
    ${CMAKE_SOURCE_DIR}/libs/cpp-lamda/include
    ${CMAKE_SOURCE_DIR}/libs/cpp-LRvalue/include
)