#ifndef __SPHERE_H__
#define __SPHERE_H__

#include <cmath>
#include <cstddef>
#include <iostream>
#include <vector>

#include "RVO.h"
#include "Visualizer.h"

#ifndef M_PI
const float M_PI = 3.14159265358979323846f;
#endif

extern std::vector<RVO::Vector3> goals;
extern RVO::Vector3 g;

void setupScenario(RVO::RVOSimulator *sim);

void updateVisualization(RVO::RVOSimulator *sim);

void setPreferredVelocities(RVO::RVOSimulator *sim);

bool reachedGoal(RVO::RVOSimulator *sim);


#endif	// __SPHERE_H__