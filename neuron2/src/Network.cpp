#include "Network.hpp"
#include <iostream>
#include <cassert>

Network::Network(double jExci, double jInhib, double poisson): m_neurons(std::vector<Neuron*>(N_NEURONS)), 
					m_connectedNeurons(N_NEURONS, std::vector<size_t>()), 
					m_jExci(jExci), m_jInhib(jInhib), m_poisson(poisson),
					rd(), gen(rd()), p(poisson)	
{
	for(size_t n(0); n < N_EXCITATORY; n++) //affect 10000 neurons to the excitatory ones
	{
		m_neurons[n] = new Neuron(true);
	}
	for(size_t n(N_EXCITATORY); n < N_NEURONS; n++) //affect 2500 neurons to the inhibitatory ones
	{
		m_neurons[n] = new Neuron(false);
	}
	
	setup();
}

Network::~Network()
{
	for(Neuron* n : m_neurons)
	{
		delete n;
	}
}

std::vector<Neuron*> Network::getNeurons() const
{
	return m_neurons;
}

std::vector<std::vector<size_t>> Network::getConnectedNeurons() const
{
	return m_connectedNeurons;
}

void Network::update()
{
	assert(m_neurons.size() == N_NEURONS); //test if the size of the table with all neurons = number of neurons we are supposed to have
	for(size_t i(0); i < m_neurons.size(); i++)
	{
		int poisson = p(gen);
		if (m_neurons[i]->update(N, 0.0, poisson)) //update the neuron with all the paramaters needed
		{
			int coeff = m_neurons[i]->isExcitatory() ? m_jExci : m_jInhib; //choose the right coeff for the buffer dependin on if 
																			//the neuron is excitator or inhibitor 
			for(size_t j : m_connectedNeurons[i])
			{
				m_neurons[j]->addJ(coeff);
			}
		}
	}
}

void Network::setup()
{
	std::random_device rd; //creation of a random number
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> uniform_exit(0, N_EXCITATORY-1); //allow random affection of excitatory connexions between the neurons (number of excitatory connexions)
    std::uniform_int_distribution<> uniform_inhib(N_EXCITATORY, N_NEURONS-1); //same but for the inhibitatory connexions
   
	for(size_t n_receiver(0); n_receiver < N_NEURONS; n_receiver++)
	{
		for(size_t i(1); i <= N_EXCITATORY_CONNEXIONS; i++) //exitatory connexions
		{
			m_connectedNeurons[uniform_exit(generator)].push_back(n_receiver);
		}
		for(size_t i(1); i <= N_INHIBITORY_CONNEXIONS; i++) //inhibitory connexions
		{
			m_connectedNeurons[uniform_inhib(generator)].push_back(n_receiver);
		}
	}
}

void Network::printSpikes(std::ofstream& fichier) const
{
	for(size_t i(0); i < m_neurons.size(); i++)
	{
		for(step s : m_neurons[i]->getSpikesTimes())
		{
			if(s >= T_START_RECORD && s <= T_STOP_RECORD)
				fichier << s*H << '\t' << i << '\n';
		}
	}
}
