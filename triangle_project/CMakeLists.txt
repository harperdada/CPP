cmake_minimum_required(VERSION 3.16)
project(triangle_project CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Header-only library: templates live in include/
add_library(triangle INTERFACE)
target_include_directories(triangle INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)

enable_testing()
find_package(GTest REQUIRED)

# Tests (note the path!)
add_executable(test_triangle ${CMAKE_CURRENT_SOURCE_DIR}/tests/test_triangle.cpp)
target_link_libraries(test_triangle PRIVATE triangle GTest::gtest_main)

add_test(NAME triangle_tests COMMAND test_triangle)

# App (optional)
add_executable(triangle_app ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
target_link_libraries(triangle_app PRIVATE triangle)

