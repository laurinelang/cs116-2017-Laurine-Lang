#include "Neuron.hpp"
#include <iostream>
#include <cassert>

using namespace std;

Neuron::Neuron(bool isExcitatory): m_membranePotential(0.0), 
									m_times(), 
									m_clock(T_START), m_j{0}, 
									m_isExcitatory(isExcitatory){}

double Neuron::getMembranePotential() const 
{
    return m_membranePotential; 
}

unsigned int Neuron::getNbSpikes() const
{
    return m_times.size();
}

std::vector<step> Neuron::getSpikesTimes() const
{
	return m_times;
}

void Neuron::addSpike(step t) 
{
	m_times.push_back(t);
}

bool Neuron::refractory(step t) const
{
	return m_times.size() != 0 and t - m_times.back() < TAO_REF; /*if there wasn't any spike (begining of the simulation) 
																* the neuron can't be refractory*/
}

bool Neuron::update (step t, double input_current, int poisson) 
{
	if(t == 0) return false;
	const step t_stop = m_clock + t;
	bool spike (false);
	
	while(m_clock < t_stop)
	{
		int indice = m_clock%m_j.size();
		if (refractory(m_clock)) //neuron is refactory 
		{
			m_membranePotential=0.0;
		} else {
			
			if(m_membranePotential >= V_TH) //if the membranePotential is >= V_th, the neuron will have a spike
			{ 
				addSpike(m_clock); //add the new spike in the table of spikes 
				m_membranePotential =0.0;
				spike = true;
			}
			else{
				m_membranePotential=(C1*m_membranePotential+input_current*C2 + (m_j[indice] + poisson)*J);
			}
		}
		m_j[indice] = 0; //"Clean" the step in which we are now 
		m_clock++;
	}
	return spike;
}

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

void Neuron::savePotential(std::ofstream& fichier)
{
	
	if(fichier.fail())
	{
		cerr << "fail to open file"<< endl;
	} else {
		fichier << m_membranePotential << endl;
	}
}

void Neuron::addJ(double coeff)  
{
	assert (D < m_j.size());
	m_j[(m_clock + D)%m_j.size()]+=coeff;
}


bool Neuron::isExcitatory() const
{
	return m_isExcitatory;
}
