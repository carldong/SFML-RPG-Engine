#ifndef __GAME_H__
#define __GAME_H__

#include <MessageBus.hpp>

class Game : public Listener {
public:
  Game(MessageBus* bus) : Listener(bus), mMessageBus(bus) {}
  void run() {}

private:
  MessageBus* mMessageBus;
};

#endif // __GAME_H__
