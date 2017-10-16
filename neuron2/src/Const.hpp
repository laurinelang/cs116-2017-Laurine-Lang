#ifndef CONST_HPP
#define CONST_HPP

const double H = 0.1; //dt
const int T_START = 100.0/H;
const int T_STOP = 400.0/H;
const double N = 1.0; //change it to run the simulation faster

const double D = 1.5; //mv
const unsigned int buffer_size = (D/H + 1);



#endif

