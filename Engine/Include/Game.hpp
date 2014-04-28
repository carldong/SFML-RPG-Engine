#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/System.hpp>
#include <iostream>

#include <MessageBus.hpp>

class Game : public Listener {
public:
  Game(MessageBus* bus);
  void run();
  void notify(Message* msg);

public:
  static const sf::Time TimePerFrame;
private:
  MessageBus* mMessageBus;
  bool mQuitFlag;
  sf::Clock mClock;
};

const sf::Time Game::TimePerFrame = sf::seconds(1.f/60.f);

#endif // __GAME_H__
