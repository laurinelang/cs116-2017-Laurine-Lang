#ifndef CONST_HPP
#define CONST_HPP

#include <vector>

typedef double Time;
typedef std::vector<Time> timesList;

const  double T_START = 0.0;
const double T_STOP =100.0;
const Time H = 0.1; //dt
const double N = 1.0; //change it to run the simulation faster

//Specific constants for the neuron
const Time TAO_REF = 2.0; //time constant in which the neuron is refractory
const Time TAO = 20.0; //time constant (tao=R*C)
const double C = 1.0; //membrane capacity
const double R = TAO / C; //membrane resistance
const double V_TH = 20; //potential threshold

#endif

