#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__
#include <Game.hpp>
#include <MessageBus.hpp>

class QuitListener : public Listener {
public:
  QuitListener(MessageBus* bus) : Listener(bus), mFail(false){}

  void notify(Message* msg) {
    if (!mFail && msg->type == Message::LogicTick) {
      Message* msgQuit = new Message(Message::Quit);
      mMessageBus->post(msgQuit);
    }
  }

  // To make a fail test case
  bool mFail;
};


#endif // __TEST_GAME_H__
