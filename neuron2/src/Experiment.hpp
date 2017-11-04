#ifndef EXPERIMENT_HPP
#define EXPERIMENT_HPP

#include "Utility.hpp"
#include "Neuron.hpp"
#include "Network.hpp"

class Experiment //!< allow simulation of the different graphs from the Brunnel
{
	public: 
		/**
		 * Run the simulation for the graph C from the Brunnel (the default graph: g=5; Vext/Vthr =2)
		 * @return void
		*/
		void runDefaultExperiment();
		
		/**
		 * Run the simulation for all the graphs from the Brunnel
		 * @return void
		*/
		void runAllExperiments();
	private: 
	
		/**
		 * Run the simulation for the graph C from the Brunnel (the default graph: g=5; Vext/Vthr =2)
		 * @param string: the name of the file in witch the spikes are writen
		 * @param double: the coeff of the current of a excitatory neuron
		 * @param double: the coeff of the current of a inhibitatory neuron
		 * @param double: Vext/Vthr, the param of the poisson distribution
		 * @return void
		*/
		void simulation(std::string fileName, double jExci = 1.0, double jInhib = -5.0, double poisson = 2.0);
	
};

#endif
