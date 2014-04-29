#ifndef __TEST_RENDERER_H__
#define __TEST_RENDERER_H__

#include <Renderer.hpp>
#include <Game.hpp>

class TestGame : public Game {
public:
  TestGame(MessageBus* bus) : Game(bus), mTicks(0) {}
  void run() {
    while (!mQuitFlag) {
      mClock.restart();
      while (mClock.getElapsedTime().asSeconds() < 0.1f); // Wait 0.5 second
      mMessageBus->post(new Message(Message::LogicTick));
      ++mTicks;
      if (mTicks == 2) mMessageBus->post(new Message(Message::Quit));
    }
  }

private:
  size_t mTicks;
};

#endif // __TEST_RENDERER_H__
