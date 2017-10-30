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

	//run simulation
	while(simtime < T_STOP)
	{
		network.update();
		simtime ++;
	}
	
	ofstream fichier("spikes.txt");
	
	network.printSpikes(fichier);
	
	fichier.close();
	
	return 0;
}

