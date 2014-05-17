#include <Game.hpp>
#include <Renderer.hpp>

/**
   Constructor of Renderer

   @param bus Pointer to messagebus
   @param width Window width
   @param height Window height
   @param title Window title
 */
Renderer::Renderer(MessageBus* bus,
                   unsigned int width, unsigned int height,
		   const std::string& title) :
  Listener(bus),
  mWindow(sf::VideoMode(width, height), title),
  mScene(nullptr), mReady(false)
{
}

/**
   Set another scene as the main scene. Changes the scene's window,
   and returns the pointer to old scene

   @param scene_ Pointer to another scene
   @return Pointer to old scene
 */
Renderer::Ptr Renderer::setScene(Ptr _scene) {
  // If scene is not empty, Renderer is ready
  mReady = _scene != nullptr;
  
  Ptr pOldScene(std::move(mScene));
  mScene = std::move(_scene);
  mScene->setWindow(&mWindow);
  return pOldScene;
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
  assert (mScene != nullptr);
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  timeSinceLastUpdate += mClock.restart();
  while (timeSinceLastUpdate > Game::TimePerFrame) {
    timeSinceLastUpdate -= Game::TimePerFrame;
    mScene->update(Game::TimePerFrame.asSeconds());
  }
}

void Renderer::notify(Message* msg) {
  switch (msg->type) {
  case Message::LogicTick:
    processEvents();
    if (mReady) {
      update();
      render();
    }
    break;
  case Message::Quit:
    mWindow.close();
    break;
  }
}

void Renderer::render() {
  assert(mScene != nullptr);
  mWindow.clear();
  mScene->draw();
  mWindow.display();
}
