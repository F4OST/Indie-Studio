//
// SpellManager.hpp for Indie-Studio in /home/gastal_r/rendu/Indie-Studio/Indie-Studio/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Sat Jun  3 18:44:20 2017 gastal_r
// Last update Thu Jun 15 22:53:56 2017 gastal_r
//

#ifndef _SPELLMANAGER_hPP
#define _SPELLMANAGER_hPP

#include      "Spell.hpp"

class SpellManager
{
public:
  SpellManager(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager, Collision::Type collisionType);
  SpellManager(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager, std::function<void(Spell::Type, const std::string &)> sendCollisionToServer, Collision::Type collisionType);

  void frameRenderingQueued(const Ogre::FrameEvent& evt);
  void launchSpell(Spell::Type type, const Ogre::Vector3 &startPos, const Ogre::Vector3 &dest);

private:
  Collision::CollisionTools &_collision;
  Ogre::SceneManager    &_sceneMgr;
  OgreOggSound::OgreOggSoundManager &_soundManager;
  size_t                _currentMaxIndex;
  std::vector<size_t>   _spellsIndex;
  std::vector<Spell *>  _spells;
  std::function<void(Spell::Type, const std::string &)> _sendCollisionToServer;
  Collision::Type       _collisionType;
  bool                  _disableCallback;
};

#endif /* !_SPELLMANAGER_hPP */
