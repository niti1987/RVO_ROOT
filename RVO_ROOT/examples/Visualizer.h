#pragma once
#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <list>

namespace RVO {
	class RVOSimulator;
}

class Visualizer
{
public:
	Visualizer( RVO::RVOSimulator * sim );

	void update();

protected:
	std::list< Ogre::SceneNode * > _visAgents;
};

