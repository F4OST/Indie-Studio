//
// Menu.cpp for Indie-Studio in /home/gastal_r/rendu/Indie-Studio/Indie-Studio/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu May 18 17:41:32 2017 gastal_r
// Last update Mon May 29 15:34:56 2017 gastal_r
//

#include        "Menu.hpp"
#include    "Entity.hpp"

Menu::Menu() :
  mPolygonRenderingMode('B'),
  mShutDown(false),
  _camera(nullptr),
  _cameraMan(nullptr),
	mRotSpd(0.1),
  mLMouseDown(false),
  mRMouseDown(false),
  mCurObject(0)
{}

Menu::~Menu()
{}

void Menu::enter(void)
{
  Ogre::LogManager::getSingletonPtr()->logMessage("===== Enter Menu =====");

  _camera = mDevice->sceneMgr->createCamera("PlayerCamMenu");
  _camera->setPosition(Ogre::Vector3(0,0,80));
  _camera->lookAt(Ogre::Vector3(0,0,-300));
  _camera->setNearClipDistance(5);

  _cameraMan = new OgreCookies::CameraMan(_camera);

  Ogre::Viewport* vp = mDevice->window->addViewport(_camera);
  vp->setBackgroundColour(Ogre::ColourValue(0,0,0));
  vp->update();
  _camera->setAspectRatio(
      Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

  createScene();
}

bool Menu::buttonPlay(const CEGUI::EventArgs &e)
{
  _playButton->destroy();
  _quitButton->destroy();
  _gameMenu->destroy();
  _myRoot->destroy();
  GameState *menu = findByName("Map");
  changeGameState(menu);
  return (true);
}

bool Menu::buttonQuit(const CEGUI::EventArgs &e)
{
  _playButton->destroy();
  _quitButton->destroy();
  _gameMenu->destroy();
  _myRoot->destroy();
  Shutdown();
  return (true);
}

bool Menu::buttonClose(const CEGUI::EventArgs &e)
{
  _closeButton->destroy();
  _credits->destroy();
  _credits = nullptr;
  return (true);
}

bool Menu::buttonInfos(const CEGUI::EventArgs &e)
{
  if (_credits == nullptr)
  {
    _credits = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Credits.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_credits);

    _closeButton = _credits->getChild("Close");
    _closeButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Menu::buttonClose, this));
  }
  return (true);
}

void Menu::createScene(void)
{
  _credits = nullptr;

  CEGUI::System::getSingleton().getDefaultGUIContext().getMouseCursor().setDefaultImage("OgreTrayImages/MouseArrow");

  _myRoot = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "_MasterRoot" );
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow( _myRoot );

  _gameMenu = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("GameMenu.layout");
  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_gameMenu);


  _playButton = _gameMenu->getChild("Play");
  _playButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Menu::buttonPlay, this));

  _quitButton = _gameMenu->getChild("Quit");
  _quitButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Menu::buttonQuit, this));

  _infosButton = _gameMenu->getChild("Infos");
  _infosButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Menu::buttonInfos, this));

  _playButton->destroy();
  _quitButton->destroy();
  _gameMenu->destroy();
  _myRoot->destroy();
  GameState *menu = findByName("Map");
  changeGameState(menu);
}

// bool GameMenuDemo::handleLoginAcceptButtonClicked(const CEGUI::EventArgs&)
// {
//     d_startButtonClickArea->setAlpha(0.0f);
//     d_startButtonBlendInAnimInst->start();
//
//     enableNavigationBarElements();
//
//     d_loginContainerMoveOutInst->start();
//     d_navigationTravelIcon->setEnabled(true);
//
//     CEGUI::Editbox* loginEditbox = static_cast<CEGUI::Editbox*>(d_root->getChild("LoginContainer/LoginEditbox"));
//     d_userName = loginEditbox->getText();
//
//     d_timeSinceLoginAccepted = 0.0f;
//     d_loginWasAccepted = true;
//     d_currentWriteFocus = WF_TopBar;
//
//     d_botNaviContainer->setEnabled(true);
//
//     return false;
// }

void Menu::exit(void)
{
  mDevice->sceneMgr->clearScene();
  mDevice->sceneMgr->destroyAllCameras();
  mDevice->window->removeAllViewports();

  Ogre::LogManager::getSingletonPtr()->logMessage("===== Exit Menu =====");
}

bool 	Menu::frameStarted(const Ogre::FrameEvent &evt)
{
  return true;
}

//-------------------------------------------------------------------------------------
bool Menu::frameRenderingQueued(const Ogre::FrameEvent& evt)
{
	if (mDevice->window->isClosed()) {
		return false;
	}

  	if (mShutDown) {
  		return false;
  	}
          mDevice->keyboard->capture();
          mDevice->mouse->capture();

     //Need to inject timestamps to CEGUI System.
    CEGUI::System::getSingleton().injectTimePulse(evt.timeSinceLastFrame);

    _cameraMan->frameRenderingQueued(evt);   // if dialog isn't up, then update the camera
    mDevice->soundManager->update(evt.timeSinceLastFrame);


    return true;
}

bool Menu::frameEnded(const Ogre::FrameEvent& evt)
{
  return (true);
}

//-------------------------------------------------------------------------------------
bool Menu::keyPressed( const OIS::KeyEvent &arg )
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

        switch (_camera->getPolygonMode())
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

        _camera->setPolygonMode(pm);
    }
    else if(arg.key == OIS::KC_F5)   // refresh all textures
    {
       Ogre::TextureManager::getSingleton().reloadAll();
    }
    else if (arg.key == OIS::KC_SYSRQ)   // take a screenshot
    {
        mDevice->window->writeContentsToTimestampedFile("screenshot", ".jpg");
    }
    else if (arg.key == OIS::KC_ESCAPE)
    {
        mShutDown = true;
        Shutdown();
    }
	else if (arg.key == OIS::KC_P)
	{
		Ogre::SceneNode *test = mDevice->sceneMgr->getSceneNode("Particle");
	}
    else
    {
        _cameraMan->injectKeyDown(arg);
    }

    return true;
}

bool Menu::keyReleased( const OIS::KeyEvent &arg )
{
    _cameraMan->injectKeyUp(arg);
    return true;
}

bool Menu::mouseMoved( const OIS::MouseEvent &arg )
{
    // _cameraMan->injectMouseMove(arg);
		CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
		context.injectMouseMove(arg.state.X.rel, arg.state.Y.rel);
		if (mLMouseDown)
		{
		}
		else if (mRMouseDown)
		{
			mCamera->yaw(Ogre::Degree(-arg.state.X.rel * mRotSpd));
			mCamera->pitch(Ogre::Degree(-arg.state.Y.rel * mRotSpd));
		}
    return true;
}

// Helper function for mouse events
CEGUI::MouseButton convertButton(OIS::MouseButtonID id)
{
  switch (id)
  {
  case OIS::MB_Left:
    return CEGUI::LeftButton;
  case OIS::MB_Right:
    return CEGUI::RightButton;
  case OIS::MB_Middle:
    return CEGUI::MiddleButton;
  default:
    return CEGUI::LeftButton;
  }
}

bool Menu::mousePressed( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
//    _cameraMan->injectMouseDown(arg, id);
CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
context.injectMouseButtonDown(convertButton(id));
//    mCameraMan->injectMouseDown(arg, id);
if (id == OIS::MB_Left)
{
mLMouseDown = true;
}
else if (id == OIS::MB_Right)
{
mRMouseDown = true;
context.getMouseCursor().hide();
}
return true;
}

bool Menu::mouseReleased( const OIS::MouseEvent &arg, OIS::MouseButtonID id )
{
//    _cameraMan->injectMouseUp(arg, id);
CEGUI::GUIContext& context = CEGUI::System::getSingleton().getDefaultGUIContext();
context.injectMouseButtonUp(convertButton(id));
if (id == OIS::MB_Left)
{
mLMouseDown = false;
}
else if (id == OIS::MB_Right)
{
mRMouseDown = false;
context.getMouseCursor().show();
}
//mCameraMan->injectMouseUp(arg, id);
    return true;
}
