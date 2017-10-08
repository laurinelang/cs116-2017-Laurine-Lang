#include "Neuron.hpp"
#include <iostream>
#include <cmath>

using namespace std;

//Constructor
Neuron::Neuron(): m_membranePotential(10), m_times(){}

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
	 if(m_times.size() == 0.0) //if there wasn't any spike (begining of the simulation) the neuron can't be refractory
	 {
		 return false;
	 }else {
		 return t - m_times.back() <= TAO_REF;
	 }
}

//update the mebrane potential of the neuron depending on if it is refractory or not
void Neuron::update (Time t, double input_current)
{
	double potential(exp(-H/TAO)*m_membranePotential);
	if (refractory(t)) //neuron refactory
	{
		m_membranePotential=0.0;
	} else { 
 		if(m_membranePotential >= V_TH){
			addSpike(t); //add the new spike in the table of spikes
			m_membranePotential =0.0;
		} else {
			m_membranePotential=(potential+input_current*R*(1-exp(-H/TAO)));
		}
	}
}

//save the time of the spike into a file
void Neuron::saveSpikes(std::ofstream& fichier)
{
	
	if(fichier.fail())
	{
		cerr << "fail to open file"<< endl;
	} else {
		fichier << "Spike times: " << endl;
		for(auto spike : getSpikesTimes())
		{
			fichier << spike << endl;
		}
	}
}

//save the membrane potential into a file
void Neuron::savePotential(std::ofstream& fichier)
{
	
	if(fichier.fail())
	{
		cerr << "fail to open file"<< endl;
	} else {
		fichier << m_membranePotential << endl;
	}
}
