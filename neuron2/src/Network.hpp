#ifndef NETWORK_HPP
#define NETWORK_HPP

#include "Utility.hpp"
#include "Neuron.hpp"
#include <vector>
#include <fstream>
#include <random>


class Network
{
	public:
		const unsigned int N_EXITATORY  = 10000;
		const unsigned int N_NEURONS = 12500;
		const unsigned int N_EXITATORY_CONNEXIONS = N_EXITATORY / 10;
		const unsigned int N_INHIBITORY_CONNEXIONS = (N_NEURONS - N_EXITATORY) / 10;
		Network();
		~Network();
		void update();
		void setup();
		void printSpikes(std::ofstream& fichier) const;
		
	private:
		std::vector<Neuron*> m_neurons;	
		std::vector<std::vector<size_t>> m_connectedNeurons;
		//std::random_device rd;
		//std::mt19937 m_gen;
		//std::poisson_distribution<> m_poiss;
		//std::vector<std::vector<int>> targets;
};
 
#endif
