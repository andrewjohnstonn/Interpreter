cmake_minimum_required(VERSION 3.16)

project(Interpreter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions("-Wall" "-g")

option(BUILD_TESTS "build bdd tests for interpreter: defaults to ON" ON)

file(GLOB interpreter_source "${CMAKE_CURRENT_SOURCE_DIR}/Public/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/Private/*.cpp")
add_library(${PROJECT_NAME} ${interpreter_source})
target_include_directories(${PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/Public")

if(BUILD_TESTS)
  set(testPath "${CMAKE_CURRENT_SOURCE_DIR}/Test")
  add_subdirectory("${testPath}/Catch2")
  #build test files into lib
  #link interpreter to test
  file(GLOB test_source "${testPath}/*.cpp")
  add_executable(${PROJECT_NAME}Test ${test_source})
  target_link_libraries(${PROJECT_NAME}Test PUBLIC Catch2::Catch2WithMain ${PROJECT_NAME})
  target_include_directories(${PROJECT_NAME}Test PRIVATE "${testPath}/Catch2/src" "${CMAKE_CURRENT_SOURCE_DIR}/Public")
endif()
