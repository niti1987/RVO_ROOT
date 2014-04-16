/*
-----------------------------------------------------------------------------
Filename:    TutorialApplication.cpp
-----------------------------------------------------------------------------

This source file is part of the
   ___                 __    __ _ _    _ 
  /___\__ _ _ __ ___  / / /\ \ (_) | _(_)
 //  // _` | '__/ _ \ \ \/  \/ / | |/ / |
/ \_// (_| | | |  __/  \  /\  /| |   <| |
\___/ \__, |_|  \___|   \/  \/ |_|_|\_\_|
      |___/                              
      Tutorial Framework
      http://www.ogre3d.org/tikiwiki/
-----------------------------------------------------------------------------
*/
#include "RVO.h"
#include "Visualizer.h"
#include "Sphere.h"

#include "TutorialApplication.h"

#include "OgreNode.h"


//-------------------------------------------------------------------------------------
TutorialApplication::TutorialApplication(void)
{

}
//-------------------------------------------------------------------------------------
TutorialApplication::~TutorialApplication(void)
{
}

bool TutorialApplication::frameStarted(const Ogre::FrameEvent& evt) {
	(void)evt;
	std::cout << "Frame update!\n";
	++mFrame;
	return true;
}



//-------------------------------------------------------------------------------------
void TutorialApplication::createScene(void)
{
    // create your scene here :)

	/* Create a new simulator instance. */
	RVO::RVOSimulator *sim = new RVO::RVOSimulator();
	
	Visualizer vis( sim );

	/* Set up the scenario. */
	setupScenario(sim);

	
    // Set the scene's ambient light
    mSceneMgr->setAmbientLight(Ogre::ColourValue(0.0f, 0.5f, 1.0f));
 
    // Create an Entity
    Ogre::Entity* sphere1_entity = mSceneMgr->createEntity("sphere1", "sphere.mesh");
 
    // Create a SceneNode and attach the Entity to it
    Ogre::SceneNode* sphere1_scene = mSceneMgr->getRootSceneNode()->createChildSceneNode("sphere1");
    sphere1_scene->attachObject(sphere1_entity);
 
	//another head
	Ogre::Entity* sphere2_entity = mSceneMgr->createEntity( "sphere2", "sphere.mesh" );
	Ogre::SceneNode* sphere2_scene = mSceneMgr->getRootSceneNode()->createChildSceneNode( "sphere2", Ogre::Vector3( 600, 0, 0 ) );
	sphere2_scene->attachObject( sphere2_entity );

    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
    light->setPosition(20.0f, 80.0f, 50.0f);

}



#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        TutorialApplication app;

        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }

        return 0;
    }

#ifdef __cplusplus
}
#endif
