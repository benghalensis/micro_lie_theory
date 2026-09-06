cmake_minimum_required(VERSION 3.16)

project(micro_lie_theory LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(micro_lie_theory INTERFACE)
target_include_directories(micro_lie_theory INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(quaternion_test tests/quaternion_test.cc)
add_executable(dual_test tests/dual_test.cc)
add_executable(simple_optimization_test tests/simple_optimization_test.cc)
target_link_libraries(quaternion_test PRIVATE micro_lie_theory)
target_link_libraries(dual_test PRIVATE micro_lie_theory)
target_link_libraries(simple_optimization_test PRIVATE micro_lie_theory)

enable_testing()
add_test(NAME quaternion_test COMMAND quaternion_test)
add_test(NAME dual_test COMMAND dual_test)
add_test(NAME simple_optimization_test COMMAND simple_optimization_test)
