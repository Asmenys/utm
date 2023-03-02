cmake_minimum_required(VERSION 3.10)

project(UniversalTuringMachine)

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

