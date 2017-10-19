#include <iostream>
#include "Neuron.hpp"
#include <cmath>
#include "gtest/gtest.h"

TEST (neuronTest, Test_mPotential)
{
	Neuron neuron;
	neuron.update(1, 1.0);
	EXPECT_NEAR(20.0*(1.0-std::exp(-0.1/20.0)),neuron.getMembranePotential(), 10e-5);
}

TEST (neuronTest, Test_spikesTimes)
{
	Neuron neuron;
	for (step i(100); i < 400; ++i)
	{
		neuron.update(i, 1.01);
	}
	EXPECT_NEAR(192.4, neuron.getSpikesTimes()[0]*H, 10e-5);
	EXPECT_NEAR(286.8, neuron.getSpikesTimes()[1]*H, 10e-5);
	EXPECT_NEAR(381.2, neuron.getSpikesTimes()[2]*H, 10e-5);
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
