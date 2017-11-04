#ifndef NEURON_HPP
#define NEURON_HPP

#include <vector>
#include <fstream>
#include <array>
#include "Utility.hpp"
#include <cmath>


class Neuron //!< represent a single neuron
{
	
	public:
		static constexpr step TAO_REF = 2.0/H; //!< time constant in which the neuron is refractory
		static constexpr double TAO = 20.0; //!< time constant (tao=R*C)
		static constexpr double C = 1.0; //!< membrane capacity
		static constexpr double R = TAO / C; //!< membrane resistance
		static constexpr double V_TH = 20; //!< potential threshold

		static constexpr double J = 0.1; //!< the current that is transfert when a neuron spikes [mv]
		static constexpr step D = 1.5/H; //!< the delay
		static constexpr size_t buffer_size = D + 1; //!< the size of the buffer
		static constexpr double C1 = exp(-H/TAO);//!< used in Neuron::update
		static constexpr double C2 = R*(1-C1);//!< used in Neuron::update
		
		/**
		 * Constructor
		 * @param bool: true if the neuron is a excitatory neuron
		*/
		Neuron(bool isExcitatory);
		
		/**
		 * Getter
		 * @return double: membrane potential of the neuron 
		*/
		double getMembranePotential() const;
		
		/**
		 * Getter
		 * @return size_t: the number of spikes of the neuron
		*/
		unsigned int getNbSpikes() const;
		
		/**
		 * Getter
		 * @return vector of time step: the times when the spikes occurs
		*/
		std::vector<step> getSpikesTimes() const;
		
		/**
		 * Add a spike at the table of spikes of the neuron (m_times)
		 * @param step: the time step when the spike occurs
		*/
		void addSpike(step t);
		
		/**
		 * update the neuron depending on if he is refractory or not
		 * @param step: the time step
		 * @param double: the input current
		 * @param int: the random number of spikes comming form outside the network (poisson distribution)
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
		 * Method that saves the membrane potential in a file
		 * @param ofstream: the file 
		 * @return void
		*/
		void savePotential(std::ofstream& fichier);
		
		/**
		 * Method that adds J to the buffer with the right coefficient
		 * @param double: the number by which we have to multiply J to have the J_inhibitory or J_excitatory 
		 * @return void
		*/
		void addJ(double coeff);
		
		/**
		 * Method that returns if the neuron is excitatory or not 
		 * @return bool: true = the neuron is excitatory
		*/
		bool isExcitatory() const;
		
	private:
	
		/**
		 * Method to see if the neuron is refractory or not
		 * @param step: the time step 
		 * @return bool: true if the neuron is refractory
		*/
		bool refractory(step t) const;
		
		double m_membranePotential; //!< bool: membrane potential
		std::vector<step> m_times; //!< vector<step> : times when the spikes occured							
		step m_clock; //!< step: the internal clock of the neuron
		std::array<int, buffer_size> m_j; //!< array<int>: the buffer (stocks the Js with the right delay and coefficient)
		bool m_isExcitatory; //!< bool: true = neuron is excitatory
};
 
#endif
