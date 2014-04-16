/*
 * Sphere.cpp
 * RVO2-3D Library
 *
 * Copyright (c) 2008-2011 University of North Carolina at Chapel Hill.
 * All rights reserved.
 *
 * Permission to use, copy, modify, and distribute this software and its
 * documentation for educational, research, and non-profit purposes, without
 * fee, and without a written agreement is hereby granted, provided that the
 * above copyright notice, this paragraph, and the following four paragraphs
 * appear in all copies.
 *
 * Permission to incorporate this software into commercial products may be
 * obtained by contacting the authors <geom@cs.unc.edu> or the Office of
 * Technology Development at the University of North Carolina at Chapel Hill
 * <otd@unc.edu>.
 *
 * This software program and documentation are copyrighted by the University of
 * North Carolina at Chapel Hill. The software program and documentation are
 * supplied "as is," without any accompanying services from the University of
 * North Carolina at Chapel Hill or the authors. The University of North
 * Carolina at Chapel Hill and the authors do not warrant that the operation of
 * the program will be uninterrupted or error-free. The end-user understands
 * that the program was developed for research purposes and is advised not to
 * rely exclusively on the program for any reason.
 *
 * IN NO EVENT SHALL THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL OR THE
 * AUTHORS BE LIABLE TO ANY PARTY FOR DIRECT, INDIRECT, SPECIAL, INCIDENTAL, OR
 * CONSEQUENTIAL DAMAGES, INCLUDING LOST PROFITS, ARISING OUT OF THE USE OF THIS
 * SOFTWARE AND ITS DOCUMENTATION, EVEN IF THE UNIVERSITY OF NORTH CAROLINA AT
 * CHAPEL HILL OR THE AUTHORS HAVE BEEN ADVISED OF THE POSSIBILITY OF SUCH
 * DAMAGE.
 *
 * THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE AUTHORS SPECIFICALLY
 * DISCLAIM ANY WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE AND ANY
 * STATUTORY WARRANTY OF NON-INFRINGEMENT. THE SOFTWARE PROVIDED HEREUNDER IS ON
 * AN "AS IS" BASIS, AND THE UNIVERSITY OF NORTH CAROLINA AT CHAPEL HILL AND THE
 * AUTHORS HAVE NO OBLIGATIONS TO PROVIDE MAINTENANCE, SUPPORT, UPDATES,
 * ENHANCEMENTS, OR MODIFICATIONS.
 *
 * Please send all bug reports to <geom@cs.unc.edu>.
 *
 * The authors may be contacted via:
 *
 * Jur van den Berg, Stephen J. Guy, Jamie Snape, Ming C. Lin, Dinesh Manocha
 * Dept. of Computer Science
 * 201 S. Columbia St.
 * Frederick P. Brooks, Jr. Computer Science Bldg.
 * Chapel Hill, N.C. 27599-3175
 * United States of America
 *
 * <http://gamma.cs.unc.edu/RVO2/>
 */

/* Example file showing a demo with 812 agents initially positioned evenly distributed on a sphere attempting to move to the antipodal position on the sphere. */

#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

#include "RVO.h"
#include "Visualizer.h"

#ifndef M_PI
const float M_PI = 3.14159265358979323846f;
#endif

/* Store the goals of the agents. */
std::vector<RVO::Vector3> goals;
RVO::Vector3 g;

void setupScenario(RVO::RVOSimulator *sim)
{
	const float timestep = 0.125;
	/* Specify the global time step of the simulation. */
	sim->setTimeStep(timestep);

	/* Specify the default parameters for agents that are subsequently added. */
	// radius set to 2.0 m because quadcopter diameter is 31 inches
	// maxNeighbors set to 1 because we have two quadcopters (for now)
	// unsure about TimeHorizon
	// neighbor distance kept at 15.0
	// maximum speed set to .2 m/s
	sim->setAgentDefaults(15.0f, 2, 40.0f, 2.0f, 0.2f);

	// print the timesetep once for the BRVO format
	std::cout << timestep << ",";

	/* Add agents, specifying their start position, and store their goals on the opposite side of the environment. */
	// one agent at 0 and one at pi/4 on a sphere
	for (float a = 0; a < M_PI/2; a += M_PI/3) {
		// assuming 40.0 m
		//std::cout << "a = " << a << " " << "anything?";
		//int qt;
		//std::cin>>qt;
		const float x = 40.0f * std::cos(a);
		const float y = 40.0f * std::sin(a);
		// constant z coordinate for altitude
		const float alt = 10.0f;

		//for (size_t i = 0; i < r / 2.5f; ++i) {
		//	const float x = r * std::cos(i * 2.0f * M_PI / (r / 2.5f));
		//	const float y = r * std::sin(i * 2.0f * M_PI / (r / 2.5f));

		sim->addAgent(RVO::Vector3(x, y, alt));
		float d = -sim->getAgentPosition(sim->getNumAgents() - 1).x();
		float e = -sim->getAgentPosition(sim->getNumAgents() - 1).y();
		float f = alt;
		g = RVO::Vector3(d,e,f);
		goals.push_back(g);
		//}
	}
}


/* Format accepted by BRVO is:
sampling interval (sec),
agentNo, positionX, positionY, positionZ
*/
void updateVisualization(RVO::RVOSimulator *sim)
{
	/* Output the current global time. */
	//std::cout << "Time: " << sim->getGlobalTime();

	/* Output the position for all the agents. */
	//std::cout << "number of agents = " << sim->getNumAgents() << "\n";
	for (size_t i = 0; i < sim->getNumAgents(); ++i) {
		RVO::Vector3 position = sim->getAgentPosition(i);
		std::cout << i << ", " << position[0] << ", " << position[1] << ", " << position[2] << "\n";
	}

	//std::cout << std::endl;
}

void setPreferredVelocities(RVO::RVOSimulator *sim)
{
	/* Set the preferred velocity to be a vector of unit magnitude (speed) in the direction of the goal. */
	for (size_t i = 0; i < sim->getNumAgents(); ++i) {
		RVO::Vector3 goalVector = goals[i] - sim->getAgentPosition(i);

		if (RVO::absSq(goalVector) > 1.0f) {
			goalVector = RVO::normalize(goalVector);
		}

		sim->setAgentPrefVelocity(i, goalVector);
	}
}

bool reachedGoal(RVO::RVOSimulator *sim)
{
	/* Check if all agents have reached their goals. */
	for (size_t i = 0; i < sim->getNumAgents(); ++i) {
		if (RVO::absSq(sim->getAgentPosition(i) - goals[i]) > 4.0f * sim->getAgentRadius(i) * sim->getAgentRadius(i)) {
			return false;
		}
	}

	return true;
}
//#if 0
//int main(int argc, const char *argv[])
//{
//	/* Create a new simulator instance. */
//	RVO::RVOSimulator *sim = new RVO::RVOSimulator();
//	Visualizer vis( sim );
//
//	/* Set up the scenario. */
//	setupScenario(sim);
//
//	/* Instantiate visualizer */
//
//
//	/* Perform (and manipulate) the simulation. */
//	do {
//		updateVisualization(sim);
//		setPreferredVelocities(sim);
//		vis.update();
//		sim->doStep();
//		// update visualization
//	}
//	while (!reachedGoal(sim));
//
//	//std::cout << "Reached goal! Do you want to quit?";
//	//int input;
//	//std::cin >> input;
//	delete sim;
//	
//	return 0;
//}
//#endif
