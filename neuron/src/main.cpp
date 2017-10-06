#include <iostream>
#include <fstream>
#include "Neuron.hpp"

using namespace std;

int main()
{
	Neuron neuron;
	ofstream fichier("spikes.txt");
	
	//Allow the user to enter data (current, time interval)
	Time simtime (T_START);
	double chosen_input_current;
	Time a(0.0);
	Time b(0.0);
	cout << "Choose an extenal current:" << endl;
	cin >> chosen_input_current;
	while (a >= b or a < 0.0 or b < 0.0)
	{
		cout << "Choose an time interval (conditions: a < b, a and b must be positive values): "; //time must be positive
		cin >> a;
		cin >> b;
	}
	cout << "[" << a << "," << b << "]" << endl;
	 
	fichier << "Membrane Potential: " << endl;
	
	//run simulation
	while(simtime < T_STOP)
	{
		double input_current(0.0);
		if(simtime >=a && simtime < b)
		{
			input_current = chosen_input_current;
		}
		neuron.savePotential(fichier); //save the membrane potential into a file
		neuron.update(simtime, input_current);  //update the membrane potential
		simtime += N*H;
	}
	
	neuron.saveSpikes(fichier); //save the time of the spikes in a file
	fichier.close();
	
	return 0;
}
