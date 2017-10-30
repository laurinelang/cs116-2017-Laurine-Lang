#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <fstream>
#include <array>
#include "Utility.hpp"
#include <cmath>


class Neuron
{
	
	public:
		//Specific constants for the neuron
		static constexpr step TAO_REF = 2.0/H; //time constant in which the neuron is refractory
		static constexpr double TAO = 20.0; //time constant (tao=R*C)
		static constexpr double C = 1.0; //membrane capacity
		static constexpr double R = TAO / C; //membrane resistance
		static constexpr double V_TH = 20; //potential threshold

		static constexpr double J = 0.1; //mv
		static constexpr step D = 1.5/H; //mv
		static constexpr size_t buffer_size = D + 1;
		static constexpr double C1 = exp(-H/TAO);
		static constexpr double C2 = R*(1-C1);
		
		/**
		 * Constructor
		 * @param bool: true if the neuron is a excitatory neuron
		*/
		Neuron(bool isExcitatory);
		/**
		 * Give the membrane potential (Getter)
		 * @return double: membrane potential of the neuron 
		*/
		double getMembranePotential() const;
		/**
		 * Give the number of spikes of the neuron
		 * @return size_t: the number of spikes
		*/
		unsigned int getNbSpikes() const;
		/**
		 * Give the times of the spikes of the neuron
		 * @return vector of time step: the times when the spikes occurs
		*/
		std::vector<step> getSpikesTimes() const;
		
		/**
		 * Add a spike at the table of spikes of the neuron (m_times)
		 * @param step: the time step when the spike occurs
		*/
		void addSpike(step t);
		
		/**
		 * update the neuron
		 * @param step: the time step
		 * @param double: the input current
		 * @return bool: true if the neuron spikes
		*/
		bool update(step t, double input_current, int poisson);
		/**
		 * Method that save the times of the spikes in a file
		 * @param ofstream: the file
		 * @return void
		*/
		void saveSpikes(std::ofstream& fichier);
		/**
		 * Method that save the membrane potential in a file
		 * @param ofstream: the file 
		 * @return void
		*/
		void savePotential(std::ofstream& fichier);
		
		//void addConnectionTo(Neuron* other);
		/**
		 * Method that add J to the buffer with the right delay
		 * @param int:the number by which we have to multiply the delay to have the J inhibitory or J excitatory 
		 * @return void
		*/
		void addJ(int coeff);
		
		bool isExcitatory() const;
		
	private:
	
		/**
		 * Method to see if the neuron is refractory or not
		 * @param step: the time step 
		 * @return bool: true if flase the neuron isn't refractory
		*/
		bool refractory(step t) const;
		
		//!< bool: membrane potential
		double m_membranePotential; 
		 
		std::vector<step> m_times; //!< vector<step> : times when the spikes occured							
		step m_clock;
		std::array<int, buffer_size> m_j;
		bool m_isExcitatory;
};
 
#endif
