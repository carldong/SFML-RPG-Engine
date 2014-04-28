#include <Game.hpp>
#include <Renderer.hpp>

/**
   Constructor of Renderer

   @param width Window width
   @param height Window height
   @param title Window title
 */
Renderer::Renderer(unsigned int width, unsigned int height,
		   const std::string& title) :
  mWindow(sf::VideoMode(width, height), title),
  mScene(mWindow) {
}

/**
   Processes events from SFML window
 */
void Renderer::processEvents() {
  sf::Event event;
  while (mWindow.pollEvent(event)) {
    switch (event.type) {
    case sf::Event::Closed:
      mMessageBus->post(new Message(Message::Quit));
      break;
    }
  }
}

/**
   Update scene
 */
void Renderer::update() {
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  timeSinceLastUpdate += mClock.restart();
  while (timeSinceLastUpdate > Game::TimePerFrame) {
    timeSinceLastUpdate -= Game::TimePerFrame;
    mScene.update(Game::TimePerFrame.asSeconds());
  }
  mScene.draw();
}

void Renderer::notify(Message* msg) {
  switch (msg->type) {
  case Message::LogicTick:
    update();
    break;
  case Message::Quit:
    mWindow.close();
    break;
  }
}
