#include <iostream>
#include "Neuron.hpp"
#include "googletest/include/gtest/gtest.h"

TEST (neuronTest, mPotential)
{
	Neuron neuron;
	neuron.setCurrent(1.0);
	
	neuron.update(1);
	EXPECT(true);
	
}


int main(int argc, char **argv){
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}
