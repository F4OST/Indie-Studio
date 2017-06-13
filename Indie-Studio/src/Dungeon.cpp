//
// Dungeon.cpp for Indie-Studio in /home/gastal_r/rendu/Indie-Studio/Indie-Studio/src/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Sun May 21 20:34:06 2017 gastal_r
// Last update Tue Jun 13 14:10:36 2017 gastal_r
//

#include        "Dungeon.hpp"

Dungeon::Dungeon() :
  GameLogic()
{}

Dungeon::~Dungeon()
{}

void Dungeon::enter(void)
{
  Ogre::LogManager::getSingletonPtr()->logMessage("===== Enter Dungeon =====");

  initGameLogic();
  createScene();
}

void Dungeon::createScene(void)
{
  _myRoot = CEGUI::WindowManager::getSingleton().createWindow( "DefaultWindow", "_MasterRoot" );
  CEGUI::System::getSingleton().getDefaultGUIContext().setRootWindow( _myRoot );

  //   Ogre::Light* spotLight = _sceneMgr->createLight("SpotLight");
  //
  // spotLight->setType(Ogre::Light::LT_SPOTLIGHT);
  // spotLight->setDiffuseColour(1.0, 1.0, 1.0);
  // spotLight->setSpecularColour(1.0, 1.0, 1.0);
  //
  // spotLight->setDirection(-1, -1, 0);
  // spotLight->setPosition(Ogre::Vector3(0, 40, 0));

  Ogre::SceneNode *map = _sceneMgr->getRootSceneNode()->createChildSceneNode("Dungeon", Ogre::Vector3(0,0,0));
  DotSceneLoader loader;
	loader.parseDotScene("dungeon.scene","General", _sceneMgr, map);
  map->setPosition({0.f, 0.f, 0.f});
  _sceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
  // return;s
  for (auto & it : loader.getLightPos())
    {
      if (it.name.find("Spot") != std::string::npos /*  ||  it.name.find("Area") != std::string::npos*/)
        continue;
        std::cout << "light: " << it.name << std::endl;
      if (it.name.find("Point") != std::string::npos)
        {
          Ogre::Light* candlelight = _sceneMgr->createLight(it.name);
          // candlelight->setDiffuseColour(Ogre::ColourValue(it.colourDiffuse.r + 1.f, it.colourDiffuse.g + 1.f, it.colourDiffuse.b + 1.f, it.colourDiffuse.a));
          // candlelight->setSpecularColour(Ogre::ColourValue(it.colourSpecular.r + 1.f, it.colourSpecular.g + 1.f, it.colourSpecular.b + 1.f, it.colourSpecular.a));
          candlelight->setDiffuseColour(it.colourDiffuse);
          candlelight->setSpecularColour(it.colourSpecular);
          candlelight->setPosition(it.pos);
          candlelight->setType(Ogre::Light::LT_POINT);
          //TODO sauvegarde des pointeurs pour les delete
          Ogre::SceneNode *test = _sceneMgr->getRootSceneNode()->createChildSceneNode("Dungeon" + std::to_string(std::rand()), it.pos);
          Ogre::ParticleSystem *_particleSystem = _sceneMgr->createParticleSystem(("EyeFireParticle") + std::to_string(std::rand()), "Space/Sun");
          test->attachObject(_particleSystem);
          candlelight->setAttenuation	(32, 0.3, 0.0014, 0.07);
          candlelight->setCastShadows(false);
        }
      else if (it.name.find("Area") != std::string::npos)
        {
          Ogre::Light* candlelight = _sceneMgr->createLight(it.name);
          // candlelight->setDiffuseColour(it.colourDiffuse + Ogre::ColourValue(1.f, 1.f, 1.f, 1.f));
          // candlelight->setSpecularColour(it.colourSpecular + Ogre::ColourValue(1.f, 1.f, 1.f, 1.f));
          candlelight->setDiffuseColour(it.colourDiffuse);
          candlelight->setSpecularColour(it.colourSpecular);
          candlelight->setPosition(it.pos);
          candlelight->setType(Ogre::Light::LT_POINT);
          candlelight->setAttenuation	(100, 1.0, 0.045, 0.0075);
          candlelight->setCastShadows(true);
        }
        else if (it.name.find("Spot") != std::string::npos)
        {
          // candlelight->setType(Ogre::Light::LT_SPOTLIGHT);
          // candlelight->setDiffuseColour(0, 0, 1.0);
          // candlelight->setSpecularColour(0, 0, 1.0);
          // // candlelight->setDiffuseColour(1, 1, 1);
          // // candlelight->setSpecularColour(1, 1, 1);
          // // candlelight->setDirection(Ogre::Vector3(0, 0, 0));
          // // candlelight->setSpotlightFalloff(1.5f);
          // candlelight->setDirection(Ogre::Vector3(it.pos.x, -1, it.pos.z));
          // candlelight->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));
          // // candlelight->setCastShadows(true);
          // candlelight->setCastShadows(true);
        }
    }
// return;
  for (auto & it : loader.dynamicObjects)
  {
    std::cout << "Dynamics ==> " << it << std::endl;
    Ogre::SceneNode *node = _sceneMgr->getSceneNode(it);
    Ogre::Entity *entity = static_cast<Ogre::Entity*>(node->getAttachedObject(0));
    Ogre::Vector3 pos(node->getPosition());
    Ogre::Quaternion orientation(node->getOrientation());

    // entity->setMaterialName("TestShadow");
    // Ogre::MaterialPtr themat = Ogre::MaterialManager::getSingleton().getByName("TestShadow");
    // Ogre::GpuProgramParametersSharedPtr mCustomAtheneVparams = themat->getTechnique(0)->getPass(1)->getShadowReceiverVertexProgramParameters();
    // Ogre::GpuProgramParametersSharedPtr mCustomAtheneFparams = themat->getTechnique(0)->getPass(1)->getShadowReceiverFragmentProgramParameters();


    if (it.find("Barrel") != std::string::npos)
    {
      Ogre::AxisAlignedBox boundingB = entity->getBoundingBox();
      Ogre::Vector3 size = boundingB.getSize();
      size = boundingB.getSize();
      size /= 2.0f;
      size *= 0.95f;
      OgreBulletCollisions::CapsuleCollisionShape *capsule = new OgreBulletCollisions::CapsuleCollisionShape(size.x, size.y, Ogre::Vector3(0, 0, 1));

      OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(it, _world.get());

      defaultBody->setShape(node,
            capsule,
            0.6f,      // dynamic body restitution
            1.f,      // dynamic body friction
            1.0f,       // dynamic bodymass
            pos,
            orientation);

        defaultBody->enableActiveState();
        _world->addRigidBody(defaultBody, 0, 0);
    }
    else
    {
      OgreBulletCollisions::StaticMeshToShapeConverter trimeshConverter(entity);
      OgreBulletCollisions::TriangleMeshCollisionShape *sceneTriMeshShape =  trimeshConverter.createTrimesh();
      OgreBulletDynamics::RigidBody *defaultBody = new OgreBulletDynamics::RigidBody(entity->getName(),  _world.get());
      defaultBody->setShape(node,
            sceneTriMeshShape,
            0.6f,      // dynamic body restitution
            1.f,      // dynamic body friction
            0.0f,       // dynamic bodymass
            pos,    // starting position of the box
            orientation);// orientation of the box

      defaultBody->enableActiveState();
      _world->addRigidBody(defaultBody,0,0);
      if (it.find("Brick") != std::string::npos || it.find("Jail") != std::string::npos
        || it.find("Wall") != std::string::npos)
      _collision->register_entity(entity, Collision::COLLISION_BOX, Collision::Type::WALL);
    }
  }
  for (auto & it : loader.staticObjects)
  {
    std::cout << "Statics ==> " << it << std::endl;
    Ogre::Entity* entity = static_cast<Ogre::Entity*>(_sceneMgr->getSceneNode(it)->getAttachedObject(0));
    _collision->register_entity(entity, Collision::COLLISION_BOX);
  }

  _ui = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("UI_IG.layout");
  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_ui);

  _settingsButton = _ui->getChild("Parameters");
  _settingsButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::buttonSettings, this));
  _creditsButton = _ui->getChild("Infos");
  _creditsButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::infosSettings, this));

  //Création du fond de la barre de sort
  switch (mDevice->data.Class)
  {
  case (Entity::Type::WARRIOR):
    _spellBar = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("WarriorSpellBar.layout");
    setupWarriorSpell();
    break;
  case (Entity::Type::WIZZARD):
    _spellBar = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("WizzardSpellBar.layout");
    setupMageSpell();
    break;
  case (Entity::Type::DARKFIEND):
    _spellBar = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("DarkFiendSpell.layout");
    setupDarkFiendSpell();
    break;
  case (Entity::Type::ENGINEER):
    _spellBar = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("IngeniorSpell.layout");
    setupIngeniorSpell();
    break;
  }

  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_spellBar);
  _healthBar = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Avatar.layout");
  CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_healthBar);
}

void Dungeon::exit(void)
{
  disconnect();

#if DEBUG_CAMERA
  delete(_cameraMan);
  _cameraMan = nullptr;
#endif
  delete(_player);
  _player = nullptr;

  _sceneMgr->destroyQuery(_rayCast);
  _rayCast = nullptr;
  _sceneMgr->destroyQuery(_collisionRayCast);
  _collisionRayCast = nullptr;

  _sceneMgr->clearScene();
  _sceneMgr->destroyAllCameras();
  mDevice->window->removeAllViewports();

  _settings = nullptr;
  _credits = nullptr;

  Ogre::LogManager::getSingletonPtr()->logMessage("===== Exit Dungeon =====");
}

bool Dungeon::buttonClose(const CEGUI::EventArgs &e)
{
  _closeButton->destroy();
  _settings->destroy();
  _settings = nullptr;
  return (true);
}

bool Dungeon::buttonMenu(const CEGUI::EventArgs &e)
{
  _closeButton->destroy();
  _settings->destroy();
  _settingsButton->destroy();
  // _goToMenuButton->destroy();
  _ui->destroy();
  _spellBar->destroy();
  _myRoot->destroy();
  GameState *menu = findByName("Menu");
  changeGameState(menu);
  return (true);
}

bool  Dungeon::infosClose(const CEGUI::EventArgs &e)
{
  _closeInfos->destroy();
  _credits->destroy();
  _credits = nullptr;
  return (true);
}

bool  Dungeon::infosSettings(const CEGUI::EventArgs &e)
{
  if (_credits == nullptr)
  {
    _credits = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("Credits.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_credits);

    _closeInfos = _credits->getChild("Close");
    _closeInfos->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::infosClose, this));
  }
  return (true);
}

bool Dungeon::buttonSettings(const CEGUI::EventArgs &e)
{
  if (_settings == nullptr)
  {
    _settings = CEGUI::WindowManager::getSingleton().loadLayoutFromFile("IG_MENU.layout");
    CEGUI::System::getSingleton().getDefaultGUIContext().getRootWindow()->addChild(_settings);

    _closeButton = _settings->getChild("Settings/BackToGame");
    _closeButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::buttonClose, this));

    _goToMenuButton = _settings->getChild("Settings/BackToMenu");
    _goToMenuButton->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::buttonMenu, this));
  }
  return (true);
}

bool  Dungeon::setupWarriorSpell()
{
  _firstSpell = _spellBar->getChild("SpellSword");
  // _firstSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellSword, this));
  _secondSpell = _spellBar->getChild("SpellEyeFire");
  // _secondSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellEyeFire, this));
  _thirdSpell = _spellBar->getChild("SpellHeart");
  // _thirdSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellHeart, this));
  _fourthSpell = _spellBar->getChild("SpellDagger");
  // _fourthSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellDagger, this));
  return (true);
}

bool  Dungeon::setupMageSpell()
{
  _firstSpell = _spellBar->getChild("SpellTornado");
  // _firstSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellTornado, this));
  _secondSpell = _spellBar->getChild("SpellFireBall");
  // _secondSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellFireBall, this));
  _thirdSpell = _spellBar->getChild("SpellShield");
  // _thirdSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellShield, this));
  _fourthSpell = _spellBar->getChild("SpellLeaf");
  // _fourthSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellLeaf, this));
  return (true);
}

bool  Dungeon::setupDarkFiendSpell()
{
  _firstSpell = _spellBar->getChild("SpellAngel");
  // _firstSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellAngel, this));
  _secondSpell = _spellBar->getChild("SpellThunderStorm");
  // _secondSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellThunderStorm, this));
  _thirdSpell = _spellBar->getChild("SpellSpectre");
  // _thirdSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellSpectre, this));
  _fourthSpell = _spellBar->getChild("SpellFire");
  // _fourthSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellFire, this));
  return (true);
}

bool  Dungeon::setupIngeniorSpell()
{
  _firstSpell = _spellBar->getChild("SpellStoneBall");
  // _firstSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellStoneBall, this));
  _secondSpell = _spellBar->getChild("SpellBullet");
  // _secondSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellBullet, this));
  _thirdSpell = _spellBar->getChild("SpellHandBeard");
  // _thirdSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellHandBeard, this));
  _fourthSpell = _spellBar->getChild("SpellIce");
  // _fourthSpell->subscribeEvent(CEGUI::Window::EventMouseClick, CEGUI::Event::Subscriber(&Dungeon::SpellIce, this));
  return (true);
}