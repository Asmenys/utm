cmake_minimum_required(VERSION 3.10)

set(PROJECT_NAME UniversalTuringMachine)

project(${PROJECT_NAME})

set(BINARY_DIR src/bin)

add_executable(
  UTM
  src/main.cpp
  ${BINARY_DIR}/symbol_node.cpp
  ${BINARY_DIR}/symbol_tree.cpp
  ${BINARY_DIR}/arg_parser.cpp
  ${BINARY_DIR}/tape.cpp
  ${BINARY_DIR}/turing_machine.cpp
  )

set(TEST_DIR ../boost_tests)

add_subdirectory(boost_tests)