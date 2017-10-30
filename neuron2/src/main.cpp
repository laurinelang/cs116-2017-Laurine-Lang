#include <iostream>
#include <fstream>
#include "Neuron.hpp"
#include "Utility.hpp"
#include "Network.hpp"

using namespace std;

int main()
{	
	
	//Allow the user to enter data (current, time interval)
	step simtime(T_START);
	Network network;

	step prev(T_START);
	//run simulation
	while(simtime < T_STOP)
	{
		if((simtime-prev)/((double)(T_STOP-T_START)) > 0.1)
		{
			std::cerr << "Simulation steps progression : "  << (simtime-T_START)/((double)(T_STOP-T_START))*100 << '\%' << std::endl;
			prev = simtime;
		}
		network.update();
		simtime ++;
	}
	
	ofstream fichier("spikes.txt");
	ofstream fichier2("spikes.ods");
	
	network.printSpikes(fichier2);
	network.printSpikes(fichier);
	
	fichier2.close();
	fichier.close();
	
	return 0;
}

