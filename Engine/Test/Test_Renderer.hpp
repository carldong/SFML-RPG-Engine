#ifndef __TEST_RENDERER_H__
#define __TEST_RENDERER_H__

#include <Renderer.hpp>
#include <Resources/Resources.hpp>
#include <Game.hpp>

#include <SFML/Graphics/RenderStates.hpp>

class TestGame : public Game {
public:
  TestGame(MessageBus* bus, size_t quitTicks=2) :
    Game(bus), mTicks(0), mTicksQuit(quitTicks) {}
  void run() {
    while (!mQuitFlag) {
      mClock.restart();
      while (mClock.getElapsedTime().asSeconds() < 0.1f); // Wait 0.1 second
      mMessageBus->post(new Message(Message::LogicTick));
      ++mTicks;
      if (mTicks == mTicksQuit) mMessageBus->post(new Message(Message::Quit));
    }
  }

private:
  size_t mTicks;
  size_t mTicksQuit;
};

class TestScene : public Scene {
public:
  TestScene(sf::RenderWindow* window) :
    Scene(window),
    mSceneBounds(0.f, 0.f, mSceneView.getSize().x, mSceneView.getSize().y),
    mTextures()
  {}
  void buildScene() final;
  
private:
  TextureHolder mTextures;
  sf::FloatRect mSceneBounds;
};

void TestScene::buildScene() {
  mTextures.load(0,"Test/assets/test_texture.png");
  sf::Texture& texture = mTextures.get(0);
  sf::IntRect textureRect(mSceneBounds);
  texture.setRepeated(true);

  std::unique_ptr<SFMLNode>
    testSprite(new SFMLSpriteNode(texture, textureRect));
  //testSprite->setPosition(0, 0);
  mSceneGraph.attachChild(std::move(testSprite));
}

#endif // __TEST_RENDERER_H__
