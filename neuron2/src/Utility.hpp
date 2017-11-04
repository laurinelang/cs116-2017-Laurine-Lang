#ifndef CONST_HPP
#define CONST_HPP

typedef unsigned int step; //define a step of time 

//Constants 
constexpr double H = 0.1; //dt
const step T_START = 100.0/H; // the time when the simulation starts
const step T_STOP = 400.0/H; // the time when the simulation stops
const step T_START_RECORD = 200.0/H; //the time to start recording spikes
const step T_STOP_RECORD = T_STOP; //the time to stop recording spikes
const double N = 1.0; // the "speed" of the simulation



#endif

