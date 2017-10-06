#ifndef NEURON_HPP
#define NEURON_HPP

#include "Const.hpp"

class Neuron
{
	
	public:
		//Constantes specifiques aux neurones
		const Time TAO_REF = 2.0;
		const Time TAO = 20.0;
		const double C = 1.0;
		const double R = TAO / C;
		const double V_TH = 20.0;
		
		//Constructeurs
		Neuron();
		//Getters
		double getMembranePotential() const;
		double getNbSpikes() const;
		timesList getSpikesTimes() const;
		
		void addSpike(Time t);
		void update(Time t, double input_current);
		
	private:
		bool refractory(Time t) const;
		
		double m_membranePotential; //the membrane potential
		timesList m_times; //times when spikes occured to have the number of spikes just look at the size of the table
};
 
#endif
