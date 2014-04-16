#include "Visualizer.h"
#include "RVOSimulator.h"
#include <iostream>

Visualizer::Visualizer( RVO::RVOSimulator * sim ):_visAgents() {
	size_t AGT_COUNT = sim->getNumAgents();
	std::cout << "There are " << AGT_COUNT << " agents\n";
}

void Visualizer::update() {
	std::cout << "update\n";
}
