#include <Game.hpp>

Game::Game(MessageBus* bus){
  mMessageBus = bus;
  mQuitFlag = false;
  mClock = sf::Clock();
  registerTo(bus);
}

Game::~Game() {

}

void Game::run() {
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (!mQuitFlag) {
    timeSinceLastUpdate += mClock.restart();
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      // DO SOMETHING
      Message* tick = new Message(Message::Type::LogicTick);
      mMessageBus->post(tick);
    }
  }
}

void Game::notify(Message* msg) {
  //std::cout << "[DEBUG]Game::notify " << msg->type << std::endl;
  if (msg->type == Message::Type::Quit) {
    std::cout << "[DEBUG]: Quit Flag Received" << std::endl;
    mQuitFlag = true;
  }
}
