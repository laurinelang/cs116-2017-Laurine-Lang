#include <iostream>
#include "Neuron.hpp"

using namespace std;

int main()
{
	Neuron neuron;
	
	Time simtime (T_START);
	double input_current;
	Time time_interval_a;
	Time time_interval_b;
	cout << "Choose an extenal current:" << endl;
	cin >> input_current;
	cout << "Choose an time interval: max ";
	cin >> time_interval_a;
	cout << ", min:" << endl;
	cin >> time_interval_b;
	 
	while(simtime < T_STOP)
	{
		neuron.update(simtime, input_current);
		simtime += H;
	}
	
	return 0;
}
