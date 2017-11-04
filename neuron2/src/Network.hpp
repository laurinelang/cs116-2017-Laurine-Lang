#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Utility.hpp"
#include "Neuron.hpp"
#include <vector>
#include <fstream>
#include <random>


class Network //!< describe the connexions, interactions between the neurons, represents a little part of the brain
{
	public:
		const unsigned int N_EXCITATORY  = 10000; //!< unsigned int: number of excitatory neurons
		const unsigned int N_NEURONS = 12500; //!< unsigned int: total number of neurons in the network
		const unsigned int N_EXCITATORY_CONNEXIONS = N_EXCITATORY / 10; //!< unsigned int: number of excitatory connexions (10% of the number of excitatory neurons in the network)
		const unsigned int N_INHIBITORY_CONNEXIONS = (N_NEURONS - N_EXCITATORY) / 10;//!< unsigned int: number of inhibitory connexions (10% of the number of inhibitory neurons in the network)
	
		/**
		 * Default constructor
		*/
		Network(double jExci = 1.0, double jInhib = -5.0, double poisson = 2.0);
		
		/**
		 * Defalut destructor
		*/
		~Network();
		
		/**
		 * Getter
		 * @return std::vector<Neuron*>: all the neurons in the network 
		*/
		std::vector<Neuron*> getNeurons() const;
		
		/**
		 * Getter
		 * @return std::vector<std::vector<size_t>>: all connected neurons in the network
		*/
		std::vector<std::vector<size_t>> getConnectedNeurons() const; 
		
		/**
		 * Update the network with all the connected neurons, call neuron->update
		 * @return void
		*/
		void update();
		
		/**
		 * Used in the constructor, fill the table of connected neurons
		 * @return void
		*/
		void setup();
		
		/**
		 * print the spikes of each neuron (time + index of the neuron) in a file
		 * @param ofstream: the file
		 * @return void
		*/
		void printSpikes(std::ofstream& fichier) const;
		
	private:
		std::vector<Neuron*> m_neurons;	//!< table with all the neurons of the network
		std::vector<std::vector<size_t>> m_connectedNeurons; //!< table with all the connexions between the neurons
		const double m_jExci; //!< the coefficient for the J_excitatory
		const double m_jInhib; //!< the coeffcient for the J_inhibitatory 
		const double m_poisson; //!< Vext/Vthr, param for the poisson distribution
		std::random_device rd; //creation of a random number
		std::mt19937 gen;
		std::poisson_distribution <> p; //creation of a poisson distribution 
		/*That should not be static as suggested because we may want to have
		 * more than one network in a simulation.
		 * /
};
 
#endif
