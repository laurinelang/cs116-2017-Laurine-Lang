cmake_minimum_required (VERSION 2.6)
project (Neuron)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/bin)
add_executable (Neuron Neuron.cpp main.cpp)
