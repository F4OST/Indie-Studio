//
// Indie.cpp for Indie.cpp in /home/gastal_r/rendu/Indie-Studio/Indie-Studio/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Thu May 18 19:40:47 2017 gastal_r
// Last update Thu May 18 21:40:05 2017 gastal_r
//

#include        "Indie.hpp"

Indie::Indie() :
  mResourcesCfg(Ogre::BLANKSTRING),
  mPluginsCfg(Ogre::BLANKSTRING)
{
  _device.ogre = nullptr;
  _device.rwindow = nullptr;
  _device.inputMgr = nullptr;
  _device.keyboard = nullptr;
  _device.mouse = nullptr;
  _device.GUISystem = nullptr;
  _device.renderer = nullptr;
  _device.window = nullptr;
  _device.soundManager = nullptr;
  _device.sceneMgr = nullptr;
  _device.camera = nullptr;
  mResourcesCfg = "resources.cfg";
  mPluginsCfg = "plugins.cfg";
  mFSLayer = OGRE_NEW_T(Ogre::FileSystemLayer, Ogre::MEMCATEGORY_GENERAL)(OGRE_VERSION_NAME);
}

Indie::~Indie()
{
  if (_device.ogre)
  {
    delete _device.ogre;
  }
  OGRE_DELETE_T(mFSLayer, FileSystemLayer, Ogre::MEMCATEGORY_GENERAL);
}

void            Indie::start()
{
  GameStateManager gameStateMgr(&_device);
  Menu::Create(&gameStateMgr, "Menu");
  gameStateMgr.start(gameStateMgr.findByName("Menu"));
}

void            Indie::setupResources()
{
  // Load resource paths from config file
  Ogre::ConfigFile cf;
  cf.load(mResourcesCfg);

    // Go through all sections & settings in the file
  Ogre::String sec, type, arch;
  Ogre::ConfigFile::SettingsBySection_::const_iterator seci;
  for(seci = cf.getSettingsBySection().begin(); seci != cf.getSettingsBySection().end(); ++seci)
  {
   sec = seci->first;
   const Ogre::ConfigFile::SettingsMultiMap& settings = seci->second;
   Ogre::ConfigFile::SettingsMultiMap::const_iterator i;
   // go through all resource paths
   for (i = settings.begin(); i != settings.end(); ++i)
   {
     type = i->first;
     arch = Ogre::FileSystemLayer::resolveBundlePath(i->second);
     Ogre::ResourceGroupManager::getSingleton().addResourceLocation(arch, type, sec);
   }
 }
}

bool            Indie::configure()
{
    // Show the configuration dialog and initialise the system
    // You can skip this and use root.restoreConfig() to load configuration
    // settings if you were sure there are valid ones saved in ogre.cfg
    if(_device.ogre->showConfigDialog())
    {
        // If returned true, user clicked OK so initialise
        // Here we choose to let the system create a default rendering window by passing 'true'
        _device.window = _device.ogre->initialise(true, "Indie Studio");

        return true;
    }
    else
    {
        return false;
    }
}

void            Indie::windowResized(Ogre::RenderWindow *rw)
{
    unsigned int width, height, depth;
    int left, top;
    rw->getMetrics(width, height, depth, left, top);

    const OIS::MouseState &ms = _device.mouse->getMouseState();
    ms.width = width;
    ms.height = height;
}

void            Indie::windowClosed(Ogre::RenderWindow *rw)
{
    //Only close for window that created OIS (the main window in these demos)
    if( rw == _device.window )
    {
        if( _device.inputMgr )
        {
            _device.inputMgr->destroyInputObject( _device.mouse );
            _device.inputMgr->destroyInputObject( _device.keyboard );

            OIS::InputManager::destroyInputSystem(_device.inputMgr);
            _device.inputMgr = 0;
        }
    }
}

void            Indie::createCamera()
{
    // Create the camera
    _device.camera = _device.sceneMgr->createCamera("PlayerCam");

    // Position it at 500 in Z direction
    _device.camera->setPosition(Ogre::Vector3(0,0,80));
    // Look back along -Z
    _device.camera->lookAt(Ogre::Vector3(0,0,-300));
    _device.camera->setNearClipDistance(5);

    //mCameraMan = new OgreCookies::CameraMan(mCamera);   // create a default camera controller
}

void            Indie::createViewports()
{
    // Create one viewport, entire window
    Ogre::Viewport* vp = _device.window->addViewport(_device.camera);
    vp->setBackgroundColour(Ogre::ColourValue(0,0,0));

    // Alter the camera aspect ratio to match the viewport
    _device.camera->setAspectRatio(
        Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
}

bool            Indie::init()
{
  _device.ogre = new Ogre::Root(mPluginsCfg, mFSLayer->getWritablePath("ogre.cfg"),
  mFSLayer->getWritablePath("ogre.log"));

  setupResources();

  _device.ogre->loadPlugin("libOgreOggSound.so");
/*    _device.ogre->loadPlugin("OgreOggSound.dll");
_device.ogre->loadPlugin("Plugin_OctreeZone.dll");
_device.ogre->loadPlugin("Plugin_PCZSceneManager.dll");
//_device.ogre->loadPlugin("Plugin_CgProgramManager.dll");
_device.ogre->loadPlugin("Plugin_OctreeSceneManager.dll");
//_device.ogre->loadPlugin("RenderSystem_GL3Plus.dll");
_device.ogre->loadPlugin("RenderSystem_GL.dll"); */

  bool carryOn = configure();
  if (!carryOn) return false;

  _device.sceneMgr = _device.ogre->createSceneManager("OctreeSceneManager");
  createCamera();
  createViewports();

  // Set default mipmap level (NB some APIs ignore this)
  Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
  // Create any resource listeners (for loading screens)

  //createResourceListener();
  // Load resources
  Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

Ogre::RenderTarget* renderTarget = _device.ogre->getRenderTarget("Indie Studio");
CEGUI::OgreRenderer& myRenderer = CEGUI::OgreRenderer::bootstrapSystem(*renderTarget);
  _device.soundManager = OgreOggSound::OgreOggSoundManager::getSingletonPtr();
  _device.soundManager->init();
  _device.soundManager->setDistanceModel(AL_LINEAR_DISTANCE);
  // Create the scene
  //createScene();
  //createFrameListener();

  Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
  OIS::ParamList pl;
  size_t windowHnd = 0;
  std::ostringstream windowHndStr;

  _device.window->getCustomAttribute("WINDOW", &windowHnd);
  windowHndStr << windowHnd;
  pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

  _device.inputMgr = OIS::InputManager::createInputSystem( pl );

  _device.keyboard = static_cast<OIS::Keyboard*>(_device.inputMgr->createInputObject( OIS::OISKeyboard, true ));
  _device.mouse = static_cast<OIS::Mouse*>(_device.inputMgr->createInputObject( OIS::OISMouse, true ));

  //_device.keyboard->setEventCallback(this);
  //_device.mouse->setEventCallback(this);
  windowResized(_device.window);
  //Register as a Window listener
  //Ogre::WindowEventUtilities::addWindowEventListener(_device.window, this);
  return true;
}