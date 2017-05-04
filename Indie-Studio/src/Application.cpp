#include "Application.hpp"

#include <OgreSceneManager.h>
#include <OgreViewport.h>
#include <OgreCamera.h>
#include <OgreRoot.h>
#include <OgreRenderWindow.h>
#include <OgreColourValue.h>
#include <OgreException.h>
#include <OIS/OISException.h>

//-------------------------------------------------------------------------------------
Application::Application() :
mDistance(0),
mWalkSpd(70.0),
mDirection(Ogre::Vector3::ZERO),
mDestination(Ogre::Vector3::ZERO),
mAnimationState(0),
mEntity(0),
mNode(0)
{
}

//-------------------------------------------------------------------------------------
Application::~Application()
{
}

//-------------------------------------------------------------------------------------
void Application::createScene()
{
	// Set the scene's ambient light
	mSceneMgr->setAmbientLight(Ogre::ColourValue(0.5f, 0.5f, 0.5f));

	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

/*
		 Ogre::Entity* ogreHead = mSceneMgr->createEntity("Head", "ogrehead.mesh");

    // Create a SceneNode and attach the Entity to it

		//Ogre::SceneNode *camera = mSceneMgr->getRootSceneNode()->createChildSceneNode("Camera");
		//mCameraMan->setTarget(camera);

    Ogre::SceneNode *headNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("HeadNode");
    headNode->attachObject(ogreHead);
		headNode->setPosition(Ogre::Vector3(0, 0, 0));

    // Create a Light and set its position
    Ogre::Light* light = mSceneMgr->createLight("MainLight");
		headNode->attachObject(light);
		light->setPosition(headNode->getPosition() + Ogre::Vector3(-84, 0, 30));
		light->setDirection(headNode->getPosition());

		Ogre::Entity* ogreEntity2 = mSceneMgr->createEntity("ogrehead.mesh");

		Ogre::SceneNode* ogreNode2 = mSceneMgr->getRootSceneNode()->createChildSceneNode(Ogre::Vector3(84, 0, 0));
		ogreNode2->attachObject(ogreEntity2); */
		mEntity = mSceneMgr->createEntity("robot.mesh");

		mNode = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		  Ogre::Vector3(0, 0, 25.0));
		mNode->attachObject(mEntity);

		mWalkList.push_back(Ogre::Vector3(550.0, 0, 50.0));
		mWalkList.push_back(Ogre::Vector3(-100.0, 0, -200.0));
		mWalkList.push_back(Ogre::Vector3(0, 0, 25.0));

		Ogre::Entity* ent;
		Ogre::SceneNode* node;

		ent = mSceneMgr->createEntity("knot.mesh");
		node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		  Ogre::Vector3(0, -10.0, 25.0));
		node->attachObject(ent);
		node->setScale(0.1, 0.1, 0.1);

		ent = mSceneMgr->createEntity("knot.mesh");
		node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		  Ogre::Vector3(550.0, -10.0, 50.0));
		node->attachObject(ent);
		node->setScale(0.1, 0.1, 0.1);

		ent = mSceneMgr->createEntity("knot.mesh");
		node = mSceneMgr->getRootSceneNode()->createChildSceneNode(
		  Ogre::Vector3(-100.0, -10.0,-200.0));
		node->attachObject(ent);
		node->setScale(0.1, 0.1, 0.1);

		mCamera->setPosition(90.0, 280.0, 535.0);
		mCamera->pitch(Ogre::Degree(-30.0));
		mCamera->yaw(Ogre::Degree(-15.0));
		mNode->showBoundingBox(true);
		mAnimationState = mEntity->getAnimationState("Idle");
mAnimationState->setLoop(true);
mAnimationState->setEnabled(true);
}

bool Application::keyPressed( const OIS::KeyEvent &arg )
{
	if (arg.key == OIS::KC_T)   // cycle polygon rendering mode
	{
			Ogre::TextureFilterOptions tfo;
			unsigned int aniso;

			switch (mPolygonRenderingMode)
			{
			case 'B':
		mPolygonRenderingMode = 'T';
					tfo = Ogre::TFO_TRILINEAR;
					aniso = 1;
					break;
			case 'T':
		mPolygonRenderingMode = 'A';
					tfo = Ogre::TFO_ANISOTROPIC;
					aniso = 8;
					break;
			case 'A':
		mPolygonRenderingMode = 'N';
					tfo = Ogre::TFO_NONE;
					aniso = 1;
					break;
			default:
		mPolygonRenderingMode = 'B';
					tfo = Ogre::TFO_BILINEAR;
					aniso = 1;
			}

			Ogre::MaterialManager::getSingleton().setDefaultTextureFiltering(tfo);
			Ogre::MaterialManager::getSingleton().setDefaultAnisotropy(aniso);
	}
	else if (arg.key == OIS::KC_R)   // cycle polygon rendering mode
	{
			Ogre::PolygonMode pm;

			switch (mCamera->getPolygonMode())
			{
			case Ogre::PM_SOLID:
					pm = Ogre::PM_WIREFRAME;
					break;
			case Ogre::PM_WIREFRAME:
					pm = Ogre::PM_POINTS;
					break;
			default:
					pm = Ogre::PM_SOLID;
			}

			mCamera->setPolygonMode(pm);
	}
	else if(arg.key == OIS::KC_F5)   // refresh all textures
	{
			Ogre::TextureManager::getSingleton().reloadAll();
	}
	else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
	{
			mWindow->writeContentsToTimestampedFile("screenshot", ".jpg");
	}
	else if (arg.key == OIS::KC_ESCAPE)
	{
			mShutDown = true;
	}
	else
	{
			mCameraMan->injectKeyDown(arg);
	}

	return true;
}