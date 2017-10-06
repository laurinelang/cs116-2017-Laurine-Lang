#ifndef NEURON_HPP
#define NEURON_HPP

#include "Const.hpp"
#include <fstream>

class Neuron
{
	
	public:
		//Constructor
		Neuron();
		//Getters
		double getMembranePotential() const;
		double getNbSpikes() const;
		timesList getSpikesTimes() const;
		
		void addSpike(Time t);
		void update(Time t, double input_current);
		void saveSpikes(std::ofstream& fichier);
		void savePotential(std::ofstream& fichier);
		//savePotential
		
	private:
		bool refractory(Time t) const;
		
		double m_membranePotential; //the membrane potential
		timesList m_times; //times when spikes occured to have the number of spikes just look at the size of the table
};
 
#endif
