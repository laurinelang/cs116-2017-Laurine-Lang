#include "Experiment.hpp"
#include <iostream>
#include <fstream>


void Experiment::simulation(std::string fileName, double jExci, double jInhib, double poisson)
{
	step simtime(T_START); //Step when the simulation starts

	step prev(T_START);
	Network network(jExci, jInhib, poisson); //initialize a network 
	//run simulation
	while(simtime < T_STOP)
	{
		if((simtime-prev)/((double)(T_STOP-T_START)) > 0.1) //Allows to display the progression % of the simulation
		{
			std::cerr << "Simulation steps progression : "  << (simtime-T_START)/((double)(T_STOP-T_START))*100 << '\%' << std::endl;
			prev = simtime;
		}
		network.update(); 
		simtime ++; // go to the next step of the simulation
	}
	
	std::ofstream fichier(fileName); //creation of a file 
	network.printSpikes(fichier); //print all the spikes and index of the neurons in a file
	fichier.close(); //close the file
}

void Experiment::runDefaultExperiment()
{
	simulation("Spikes.txt"); //Brunnel graphe C
}

void Experiment::runAllExperiments()
{
	std::cout << "simulation A: " << std::endl;
	simulation("Spikes_Brunnel_A.txt", 1.0, -3.0, 2.0);
	std::cout << "simulation B: " << std::endl;
	simulation("Spikes_Brunnel_B.txt", 1.0, -6, 4.0);
	std::cout << "simulation C: " << std::endl;
	simulation("Spikes_Brunnel_C.txt");
	std::cout << "simulation D: " << std::endl;
	simulation("Spikes_Brunnel_D.txt", 1.0, -4.5, 0.9);
}
	
