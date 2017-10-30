#include "Network.hpp"
#include <iostream>

Network::Network(): m_neurons(std::vector<Neuron*>(N_NEURONS)), 
					m_connectedNeurons(N_NEURONS, 
					std::vector<int>(N_NEURONS)),
					m_gen(std::random_device()()),
					m_poiss(2)	
{					
	for(size_t n(0); n < N_EXITATORY; n++)
	{
		m_neurons[n] = new Neuron(true);
	}
	for(size_t n(N_EXITATORY); n < N_NEURONS; n++)
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

void Network::update()
{
	for(size_t i(0); i < m_neurons.size(); i++)
	{
		double v = (m_poiss(m_gen));
		//std::cerr << v << std::endl;
		if (m_neurons[i]->update(N, v) ) //update the membrane potential, depending on if the neuron get the current or not
		{
			for(size_t j(0); j < N_EXITATORY_CONNEXIONS; j++)
			{
				m_neurons[j]->addJ(m_connectedNeurons[i][j]);
			}
			for(size_t j(N_EXITATORY_CONNEXIONS); j < N_EXITATORY_CONNEXIONS + N_INHIBITORY_CONNEXIONS; j++)
			{
				m_neurons[j]->addJ(-5 * m_connectedNeurons[i][j]);
			}
		}
	}
}

void Network::setup()
{
	std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> uniform_exit(0, N_EXITATORY_CONNEXIONS-1);
    std::uniform_int_distribution<> uniform_inhib(N_EXITATORY_CONNEXIONS, N_EXITATORY_CONNEXIONS + N_INHIBITORY_CONNEXIONS);
    
	for(size_t n_receiver(0); n_receiver < N_NEURONS; n_receiver++)
	{
		//exitatory connexions
		for(size_t i(1); i <= N_EXITATORY_CONNEXIONS; i++)
		{
			m_connectedNeurons[uniform_exit(generator)][n_receiver]++;
		}
		//inhibitory connexions
		for(size_t i(1); i <= N_INHIBITORY_CONNEXIONS; i++)
		{
			m_connectedNeurons[uniform_inhib(generator)][n_receiver]++;
		}
	}
}

void Network::printSpikes(std::ofstream& fichier) const
{
	for(size_t i(0); i < m_neurons.size(); i++)
	{
		for(step s : m_neurons[i]->getSpikesTimes())
		{
			fichier << i << '\t' << s * H << std::endl;
		}
	}
}
