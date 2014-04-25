#ifndef __GAME_H__
#define __GAME_H__

#include <SFML/System.hpp>
#include <iostream>

#include <MessageBus.hpp>

class Game : public Listener {
public:
  Game(MessageBus* bus);
  ~Game();
  void run();
  void notify(Message* msg);

public:
  const sf::Time TimePerFrame = sf::seconds(1.f/60.f);
private:
  MessageBus* mMessageBus;
  bool mQuitFlag;
  sf::Clock mClock;
};

#endif // __GAME_H__
