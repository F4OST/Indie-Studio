//
// AllSpells.hpp for Indie-Studio in /home/gastal_r/rendu/Indie-Studio/Indie-Studio/include/
//
// Made by gastal_r
// Login   <remi.gastaldi@epitech.eu>
//
// Started on  Sat Jun 10 16:33:57 2017 gastal_r
// Last update Tue Jun 20 02:06:56 2017 gastal_r
//

#ifndef     _ALLSPELLS_HPP_
#define     _ALLSPELLS_HPP_

#include    "Spell.hpp"

/*-----------------------------------------------------------------------------
|  Warrior
-----------------------------------------------------------------------------*/
#define     EYE_FIRE_SPEED 4.f
#define     EYE_FIRE_DISTANCE 10.f
#define     EYE_FIRE_COOLDOWN 6
class EyeFire : public Spell
{
public:
  EyeFire(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     SWORD_SPEED 4.f
#define     SWORD_DISTANCE 20.f
#define     SWORD_COOLDOWN 0.5
class Sword : public Spell
{
public:
  Sword(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
    size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     HEARTH_SPEED 4.f
#define     HEARTH_DISTANCE 20.f
#define     HEARTH_COOLDOWN 2
class Hearth : public Spell
{
public:
  Hearth(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
    size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     DAGGER_SPEED 30.f
#define     DAGGER_DISTANCE 6.f
#define     DAGGER_COOLDOWN 0.5
class Dagger : public Spell
{
public:
  Dagger(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
    size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};


/*-----------------------------------------------------------------------------
|  Wizard
-----------------------------------------------------------------------------*/
#define     TORNADO_SPEED 4.f
#define     TORNADO_DISTANCE 20.f
#define     TORNADO_COOLDOWN 4
class Tornado : public Spell
{
public:
  Tornado(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     FIREBALL_SPEED 10.f
#define     FIREBALL_DISTANCE 20.f
#define     FIREBALL_COOLDOWN 1
class Fireball : public Spell
{
public:
  Fireball(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     SHIELD_BUFF_SPEED 4.f
#define     SHIELD_BUFF_DISTANCE 20.f
#define     SHIELD_BUFF_COOLDOWN 9
class ShieldBuff : public Spell
{
public:
  ShieldBuff(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     LEAF_BUFF_SPEED 4.f
#define     LEAF_BUFF_DISTANCE 20.f
#define     LEAF_BUFF_COOLDOWN 9
class LeafBuff : public Spell
{
public:
  LeafBuff(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};


/*-----------------------------------------------------------------------------
|  DarkFiend
-----------------------------------------------------------------------------*/
#define     ANGEL_SPEED 6.f
#define     ANGEL_DISTANCE 15.f
#define     ANGEL_COOLDOWN 3
class Angel : public Spell
{
public:
  Angel(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     FIRE_SPEED 20.f
#define     FIRE_DISTANCE 10.f
#define     FIRE_COOLDOWN 3
class Fire : public Spell
{
public:
  Fire(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     THUNDERSTORM_SPEED 8.f
#define     THUNDERSTORM_DISTANCE 7.f
#define     THUNDERSTORM_COOLDOWN 8
class Thunderstorm : public Spell
{
public:
  Thunderstorm(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     FIRESTORM_SPEED 5.f
#define     FIRESTORM_DISTANCE 15.f
#define     FIRESTORM_COOLDOWN 6
class FireStorm : public Spell
{
public:
	FireStorm(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};



/*-----------------------------------------------------------------------------
|  Engineer
-----------------------------------------------------------------------------*/

#define     STONEBALL_SPEED 5.f
#define     STONEBALL_DISTANCE 15.f
#define     STONEBALL_COOLDOWN 1.5f
class StoneBall : public Spell
{
public:
  StoneBall(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     STALACTITES_SPEED 14.f
#define     STALACTITES_DISTANCE 20.f
#define     STALACTITES_COOLDOWN 5.f
class Stalactites : public Spell
{
public:
  Stalactites(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     BULLET_SPEED 2.f
#define     BULLET_DISTANCE 20.f
#define     BULLET_COOLDOWN 8.f
class Bullet : public Spell
{
public:
  Bullet(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#define     BEAR_BUFF_SPEED 4.f
#define     BEAR_BUFF_DISTANCE 20.f
#define     BEAR_BUFF_COOLDOWN 9.f
class BearBuff : public Spell
{
public:
  BearBuff(Ogre::SceneManager &sceneMgr, Collision::CollisionTools &collision, OgreOggSound::OgreOggSoundManager &soundManager,
  size_t id, const Ogre::Vector3 &position, const Ogre::Vector3 &destination, Collision::Type collisionType, bool disableCallback);
};

#endif /* !_ALLSPELLS_HPP_ */
