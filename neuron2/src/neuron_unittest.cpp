#include <iostream>
#include "Neuron.hpp"
#include <cmath>
#include "googletest/include/gtest/gtest.h"

TEST (neuronTest, Test_mPotential)
{
	Neuron neuron;
	neuron.update(1, 1.0);
	
	EXPECT_EQ(20.0*(1.0-std::exp(-1.0/20.0)),neuron.getMembranePotential());
}

TEST (neuronTest, Test_spikesTimes)
{
	Neuron neuron;
	for (step i(100); i < 400; ++i)
	{
		neuron.update(i, 1.01);
	}
	EXPECT_EQ(192.4, neuron.getSpikesTimes()[0])
	EXPECT_EQ(286.8, neuron.getSpikesTimes()[1])
	EXPECT_EQ(381.2, neuron.getSpikesTimes()[2])
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
