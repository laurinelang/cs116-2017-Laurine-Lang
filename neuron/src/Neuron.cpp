#include "Neuron.hpp"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor
Neuron::Neuron(): m_membranePotential(10), m_times({-TAO_REF - 1}){}

//Getters
double Neuron::getMembranePotential() const
{
    return m_membranePotential;
}

double Neuron::getNbSpikes() const
{
    return m_times.size() - 1;
}

timesList Neuron::getSpikesTimes() const
{
	return m_times;
}

//add a spike to the table of times
void Neuron::addSpike(Time t) 
{
	m_times.push_back(t);
}

//Method to see if the neuron il refractory or not (true/flase)
bool Neuron::refractory(Time t) const
{
	 return t - m_times.back() <= TAO_REF;
}


//update the mebrane potential of the neuron depending on if he is refractory or not
void Neuron::update (Time t, double input_current)
{
	if (refractory(t)) //neuron refactory
	{
		m_membranePotential=exp(-H/TAO)*m_membranePotential;
	} else{
		m_membranePotential=exp(-H/TAO)*m_membranePotential + input_current*R*(1-exp(-H/TAO));
		if(m_membranePotential >= V_TH){
			addSpike(t); //add the new spike in the table of spikes
		}
	}
}
