cmake_minimum_required(VERSION 3.10)

project(UnitTests)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ".")
set(PROJECT_UNIT_TESTS_NAME ${PROJECT_NAME}_unit_tests)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

add_executable(
    test_unit
    ${TEST_DIR}/utm_tests.cpp
    ${TEST_DIR}/tape_tests.cpp
    )

target_link_libraries(test_unit Boost::unit_test_framework)
target_compile_definitions(test_unit PUBLIC BOOST_TEST_DYN_LINK)

enable_testing()
add_test(test_unit test_unit)