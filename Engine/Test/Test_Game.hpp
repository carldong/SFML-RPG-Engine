#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__
#include <Game.hpp>
#include <MessageBus.hpp>

class QuitListener : public Listener {
public:
  QuitListener(MessageBus* bus) : Listener(bus){}

  void notify(Message* msg) {
    if (msg->type == Message::LogicTick) {
      Message* msgQuit = new Message(Message::Quit);
      mMessageBus->post(msgQuit);
    }
  }
};


#endif // __TEST_GAME_H__
