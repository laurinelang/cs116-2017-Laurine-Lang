cmake_minimum_required (VERSION 2.6)
project (Neuron)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)

enable_testing()
add_subdirectory(gtest)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable (../bin/Neuron Neuron.cpp main.cpp)
add_executable(neuron_unittest Neuron.cpp neuron_unittest.cpp)

target_link_libraries(neuron_unittest gtest gtest_main)
add_test(neuron_unittest neuron_unittest)

