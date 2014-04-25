#include <Renderer.hpp>

Renderer::Renderer(unsigned int width, unsigned int height,
		   const std::string& title) :
  mWindow(sf::VideoMode(width, height), title){
}

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

void Renderer::update() {
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
