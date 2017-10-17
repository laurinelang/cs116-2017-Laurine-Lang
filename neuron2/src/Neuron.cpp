#include "Neuron.hpp"
#include <iostream>
#include <cmath>
#include <cassert>

using namespace std;

//Constructor
Neuron::Neuron(): m_membranePotential(0.0), m_times(), m_clock(T_START), m_j{0}{}

//Getters
double Neuron::getMembranePotential() const
{
    return m_membranePotential;
}

double Neuron::getNbSpikes() const
{
    return m_times.size();
}

std::vector<step> Neuron::getSpikesTimes() const
{
	return m_times;
}

//add a spike to the table of times
void Neuron::addSpike(step t) 
{
	m_times.push_back(t);
}

//Method to see if the neuron is refractory or not (true/flase)
bool Neuron::refractory(step t) const
{
	 if(m_times.size() == 0.0) //if there wasn't any spike (begining of the simulation) the neuron can't be refractory
	 {
		 return false;
	 }else {
		 return t - m_times.back() < TAO_REF;
	 }
}

//update the mebrane potential of the neuron depending on if it is refractory or not
bool Neuron::update (step t, double input_current)
{
	if(t == 0) return false;
	const step t_stop = m_clock + t;
	bool spike (false);
	
	while(m_clock < t_stop){
		if (refractory(m_clock)) //neuron refactory 
		{
			m_membranePotential=0.0;
		} else {
			
			if(m_membranePotential >= V_TH) //if the membranePotential is >= V_th, the neuron will have a spike
			{ 
				addSpike(m_clock); //add the new spike in the table of spikes 
				m_membranePotential =0.0;
				for(auto neuron : m_connectedNeurons)
				{
					neuron->addJ(D/H); //Add the value of J to the neurons connected to the one who spike (whith a delay)
				}
				spike = true;
			}
			else{	
				m_membranePotential=(exp(-H/TAO)*m_membranePotential+input_current*R*(1-exp(-H/TAO)) + m_j[m_clock%m_j.size()]*J);
				m_j[m_clock%m_j.size()] = 0; //"Clean" the step in which we are now 
			}
		}
		m_clock++;
	}
	return spike;
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
			fichier << spike*H << endl; //to have [ms]
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


void Neuron::addConnectionTo(Neuron* other) //Add connections to the neuron 
{
	m_connectedNeurons.push_back(other);
}

void Neuron::addJ(step delay) //Add J the the buffer (with the right delay) 
{
	assert(delay < m_j.size());
	m_j[(m_clock + delay)%m_j.size()]++;
}

