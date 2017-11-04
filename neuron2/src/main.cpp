#include <iostream>
#include "Neuron.hpp"
#include "Utility.hpp"
#include "Network.hpp"
#include "Experiment.hpp"
#include <time.h>

using namespace std;

int main(int argc, char ** argv) //this paramaters allow to run one graph or all the graph (see the README)
{	
	clock_t start, stop; 
	start = clock(); //initialize the clock
	
	Experiment exp; //creation of a experiment
	if (argc <= 1 ) //if no parameter in main() 
	{
		exp.runDefaultExperiment(); //run the specific graph 
	} else if(argc == 2 && ((string)argv[1]).length() == 1 && argv[1][0] == 'a') { //if a parameter is added to the main
		exp.runAllExperiments(); //run all the graphs
	}
	else{
		cerr << "Argument unknown or too many arguments. Read README.txt for more informations.\nHave a nice day!" << endl;
		return 1;
	}
	
	stop = clock(); //"stop" the clock
	double timeSimulation = (double)(stop-start)/CLOCKS_PER_SEC; //Allow to show the progression of the simultation
	std::cout << "Simulation time: " << timeSimulation << "[s]" << std::endl; //display the progression on the terminal
	
	return 0;
}

