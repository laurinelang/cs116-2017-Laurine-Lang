#include <iostream>
#include <fstream>
#include "Neuron.hpp"
#include "Const.hpp"

using namespace std;

int main()
{
	Neuron neuron;
	ofstream fichier("spikes.txt");
	
	//Allow the user to enter data (current, time interval)
	step simtime(0);
	double chosen_input_current;
	step a(0);
	step b(0);
	cout << "Choose an extenal current:" << endl;
	cin >> chosen_input_current;
	while (a >= b or a < 0 or b < 0)
	{
		double s(0.0), e(0.0);
		cout << "Choose an time interval (conditions: a < b, a and b must be positive values): "; //time must be positive
		cin >> s;
		cin >> e;
		cout << "[" << s << "," << e << "]" << endl;
		a = s/H;
		b = e/H;
	}
	 
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
		if (neuron.update(1, input_current))  //update the membrane potential
		{
			cout << "Spike time: " << simtime*H  << " ms" << endl;
		}
		simtime ++;
	}
	
	neuron.saveSpikes(fichier); //save the time of the spikes in a file
	fichier.close();
	
	return 0;
}
