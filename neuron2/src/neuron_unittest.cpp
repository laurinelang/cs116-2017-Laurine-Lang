#include <iostream>
#include "Neuron.hpp"
#include "Network.hpp"
#include <cmath>
#include "gtest/gtest.h"

TEST (neuronTest, Test_mPotential) //Test the membran potential with a current of 1.0 and a current of 0
{
	Neuron neuron1(true);
	Neuron neuron2(true);
	neuron1.update(1, 1.0, 0);
	EXPECT_NEAR(20.0*(1.0-std::exp(-0.1/20.0)),neuron1.getMembranePotential(), 10e-10);
	
	neuron1.update(10000, 1.0, 0);
	EXPECT_GT(10e-3, std::fabs(19.999 - neuron1.getMembranePotential()));
	
	neuron2.update(1, 0.0, 0);
	EXPECT_NEAR(0, neuron2.getMembranePotential(), 10e-10);
}

TEST (neuronTest, Test_spikesTimes) //test the spikes times for a current of 1.01 without connected neurons
{
	Neuron neuron1(true);
	for (step i(100); i < 400; ++i)
	{
		neuron1.update(i, 1.01, 0);
	}
	EXPECT_NEAR(192.4, neuron1.getSpikesTimes()[0]*H, 10e-10);
	EXPECT_NEAR(286.8, neuron1.getSpikesTimes()[1]*H, 10e-10);
	EXPECT_NEAR(381.2, neuron1.getSpikesTimes()[2]*H, 10e-10);
}

TEST (neuronTest, Test_nbSpikes) //Test the number of spikes the neuron is supposed to have depending on the step (current of 1.01)
{
	Neuron neuron(true);
	neuron.update(924, 1.01, 0);
	EXPECT_EQ((unsigned int)0, neuron.getNbSpikes());
	
	neuron.update(1, 1.01, 0);
	EXPECT_EQ((unsigned int)1, neuron.getNbSpikes());
}

TEST (neuronTest, Connexion) //Test the buffer between two neurons
{
	Neuron neuron1 (true);
	Neuron neuron2 (true);
	double coeff (1); 
	step delay (1.5/H);
	
	for (step i(0); i < 925 + delay; ++i)
	{
		if(neuron1.update(1, 1.01, 0))
		{
			neuron2.addJ(coeff);
		}
		neuron2.update(1, 0, 0);
	}
	
	EXPECT_NEAR (0.1, neuron2.getMembranePotential(), 10e-10);
	EXPECT_EQ((unsigned int)1, neuron1.getNbSpikes());
}

TEST (neuronTest, testNbConnexions) //Test the size of the table of connexion
{
	Network network;
	int sum(0);
	int supposedConnexions = 12500*1250;
	for(auto vec : network.getConnectedNeurons())
	{
		sum+=vec.size();
	}
	EXPECT_NEAR(sum, supposedConnexions, 10e-2);
}

TEST(neuronTest, testExcitatory) //test if the neurons excitatory are really excitatory
{
	Network network; 
	unsigned int n_excitatory(10000);
	for(size_t i(0); i < network.getNeurons().size(); ++i)
	{
		if(i < n_excitatory)
		{
			ASSERT_TRUE(network.getNeurons()[i]->isExcitatory());
		} else {
			ASSERT_FALSE(network.getNeurons()[i]->isExcitatory());
		}
	}
}

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

