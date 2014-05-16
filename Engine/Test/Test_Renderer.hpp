#ifndef __TEST_RENDERER_H__
#define __TEST_RENDERER_H__

#include <Renderer.hpp>
#include <Resources/Resources.hpp>
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

// TODO: Finish this
class TestScene : public Scene {
public:
  using Scene::Scene;
  void buildScene() final;
  
private:
  TextureHolder mTextures;
};

void TestScene::buildScene() {
  mTextures.load(0,"Test/assets/test_texture.png");
}

#endif // __TEST_RENDERER_H__
