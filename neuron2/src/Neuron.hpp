#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <fstream>
#include <array>
#include "Const.hpp"

typedef unsigned int step;

class Neuron
{
	
	public:
		//Specific constants for the neuron
		const step TAO_REF = 2.0/H; //time constant in which the neuron is refractory
		const double TAO = 20.0; //time constant (tao=R*C)
		const double C = 1.0; //membrane capacity
		const double R = TAO / C; //membrane resistance
		const double V_TH = 20; //potential threshold

		const double J = 0.1; //mv
		
		//Constructor
		Neuron();
		//Getters
		double getMembranePotential() const;
		double getNbSpikes() const;
		std::vector<step> getSpikesTimes() const;
		
		void addSpike(step t);
		bool update(step t, double input_current);
		void saveSpikes(std::ofstream& fichier);
		void savePotential(std::ofstream& fichier);
		void addConnectionTo(Neuron* other);
		void addJ(step delay);
		
	private:
		bool refractory(step t) const;
		
		double m_membranePotential; //the membrane potential
		std::vector<step> m_times; /*times when spikes occured to have the number 
							*of spikes just look at the size of the table
							*/
		step m_clock;
		std::vector<Neuron*> m_connectedNeurons;
		std::array<int, 5> m_j;
};
 
#endif
