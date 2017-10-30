#include "Network.hpp"
#include <iostream>
#include <cassert>

Network::Network(): m_neurons(std::vector<Neuron*>(N_NEURONS)), 
					m_connectedNeurons(N_NEURONS, 
					std::vector<size_t>())
					//m_gen(std::random_device()()),
					//m_poiss(2)	
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
	static std::random_device rd;
	static std::mt19937 gen(rd());
	static std::poisson_distribution <> p(2);
	assert(m_neurons.size() == N_NEURONS);
	for(size_t i(0); i < m_neurons.size(); i++)
	{
		int poisson = p(gen);
		//double v = (m_poiss(m_gen));
		//std::cerr << v << std::endl;
		if (m_neurons[i]->update(N, 0.0, poisson)) //update the membrane potential, depending on if the neuron get the current or not
		{
			int coeff = m_neurons[i]->isExcitatory() ? 1 : -5;
			for(size_t j : m_connectedNeurons[i])
			{
				m_neurons[j]->addJ(coeff);
			}
		}
	}
}

void Network::setup()
{
	std::random_device rd;
    std::mt19937 generator(rd());
    std::uniform_int_distribution<> uniform_exit(0, N_EXITATORY-1);
    std::uniform_int_distribution<> uniform_inhib(N_EXITATORY, N_NEURONS-1);
    
	for(size_t n_receiver(0); n_receiver < N_NEURONS; n_receiver++)
	{
		//exitatory connexions
		for(size_t i(1); i <= N_EXITATORY_CONNEXIONS; i++)
		{
			//m_connectedNeurons[uniform_exit(generator)][n_receiver]++;
			m_connectedNeurons[uniform_exit(generator)].push_back(n_receiver);
		}
		//inhibitory connexions
		for(size_t i(1); i <= N_INHIBITORY_CONNEXIONS; i++)
		{
			//m_connectedNeurons[uniform_inhib(generator)][n_receiver]++;
			m_connectedNeurons[uniform_inhib(generator)].push_back(n_receiver);
		}
	}
	///A mettre en test XD
	int sum(0);
	for(auto vec : m_connectedNeurons)
	{
		sum+=vec.size();
	}
	std::cerr << "T'as oublié de me mettre en test patate !" << std::endl;
	assert(sum == 12500*1250);
}

void Network::printSpikes(std::ofstream& fichier) const
{
	for(size_t i(0); i < m_neurons.size(); i++)
	{
		for(step s : m_neurons[i]->getSpikesTimes())
		{
			fichier << s*H << '\t' << i << '\n';
		}
	}
}
