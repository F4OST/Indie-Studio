//
// client.hpp for Indie-Studio in /home/prost_m/Rendu/Semestre_4/Indie-Studio-socket/Socket-Studio/inc/
//
// Made by Matthias Prost
// Login   <matthias.prost@epitech.eu@epitech.eu>
//
// Started on  Sat May  6 13:22:30 2017 Matthias Prost
// Last update Sun Jun 18 02:57:54 2017 Leo HUBERT
//

#ifndef _CLIENT_HPP_
#define _CLIENT_HPP_

#include "WorkingQueue.hpp"

#define SOCKET_SERVER "http://ezgames.eu"
#define SOCKET_PORT 3000

#ifdef WIN32
#define EM(__O__) std::cout<<__O__<<std::endl
#define HIGHLIGHT(__O__) std::cout<<__O__<<std::endl
#define HIGHLIGHT_N(__O__) std::cout<<__O__


#include <tchar.h>
#include <stdio.h>

#else
#define HIGHLIGHT_N(__O__) std::cout<<"\e[1;31m"<<__O__<<"\e[0m"
#define EM(__O__) std::cout<<"\e[1;30;1m"<<__O__<<"\e[0m"<<std::endl
#define HIGHLIGHT(__O__) std::cout<<"\e[1;31m"<<__O__<<"\e[0m"<<std::endl

#endif

class Socket : virtual private WorkingQueue
{
public:
  Socket(std::string const &, int const, int const, std::string const &);
  ~Socket();
  void  on_connected();
  void  on_close(sio::client::close_reason const&);
  void  on_fail();
  void  events();
  void  connect();
  void  disconnect();
  void  wait();
  void  consoleChat();
  void  sendLogin(const bool);
  void  emit(const std::string &event, std::shared_ptr<sio::message> const &);
  void  move(const Entity &);
  void  refreshPos(const Entity &);

  void sendCollision(Spell::Type, const std::string &);
  void sendMessage(std::string const &);
  void sendEntity(const Entity &);
  void sendSpell(Spell::Type, const Ogre::Vector3 &, const Ogre::Vector3 &);

private:
  std::mutex                  _lock;
  std::condition_variable_any _cond;
  bool                        _connect_finish;
  size_t                      _connections;
  sio::socket::ptr            _current_socket;
  sio::client                 _client;
  std::string                 _addr;
  std::string                 _room;

protected:
  bool                        _killed;
  int                         _id;
};

#endif /* _CLIENT_HPP_ */
