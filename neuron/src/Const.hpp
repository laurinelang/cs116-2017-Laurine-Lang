#ifndef CONST_HPP
#define CONST_HPP

#include <vector>

typedef double Time;
typedef std::vector<Time> timesList;

const  double T_START = 0.0;
const double T_STOP =60.0;
const Time H = 0.1;

#endif


// g++ -c neuron.cpp main.cpp
// g++ neuron.cpp main.cpp -o main
// ./main
