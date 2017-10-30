#include <iostream>
#include "Neuron.hpp"
#include <cmath>
#include "gtest/gtest.h"

/*TEST (neuronTest, Test_mPotential)
{
	Neuron neuron1;
	Neuron neuron2;
	neuron1.update(1, 1.0);
	EXPECT_NEAR(20.0*(1.0-std::exp(-0.1/20.0)),neuron1.getMembranePotential(), 10e-5);
	
	neuron1.update(10000, 1.0);
	EXPECT_GT(10e-3, std::fabs(19.999 - neuron1.getMembranePotential()));
	
	neuron2.update(1, 0.0);
	EXPECT_NEAR(0, neuron2.getMembranePotential(), 10e-5);
}*/

/*TEST (neuronTest, Test_spikesTimes)
{
	Neuron neuron1;
	Neuron neuron2;
	for (step i(100); i < 400; ++i)
	{
		neuron1.update(i, 1.01);
	}
	EXPECT_NEAR(192.4, neuron1.getSpikesTimes()[0]*H, 10e-5);
	EXPECT_NEAR(286.8, neuron1.getSpikesTimes()[1]*H, 10e-5);
	EXPECT_NEAR(381.2, neuron1.getSpikesTimes()[2]*H, 10e-5);
	
	for (unsigned int i(0); i < neuron1.getNbSpikes() + 1; ++i)
	{
		neuron2.update((neuron1.getSpikesTimes()[i]*H + 1), 1.01);
	}
	neuron2.update(925, 1.01);
	EXPECT_EQ(0, neuron2.getMembranePotential()); //MANQUE LES AUTRES
}

TEST (neuronTest, Test_nbSpikes)
{
	Neuron neuron;
	neuron.update(924, 1.01);
	EXPECT_EQ(0, neuron.getNbSpikes());
	
	neuron.update(1, 1.01);
	EXPECT_EQ(1, neuron.getNbSpikes());
}

TEST (neuronTest, Connexion)
{
	Neuron neuron1;
	Neuron neuron2;
	step delay (15); 
	
	for (auto i(0); 1 < 925 + delay; ++i)
	{
		if(neuron1.update(i, 1.01))
		{
			neuron2.addJ(delay);
			EXPECT_EQ (0.0, neuron1.getMembranePotential());
		}
		neuron2.update(i, 1.01);
		//EXPECT_NEAR(0.1*neuron1.getNbSpikes(), neuron2.getMembranePotential(), 10e-2);
	}
}

TEST ()
{
	
}*/

int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

