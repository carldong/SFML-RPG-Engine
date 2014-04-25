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
    timeSinceLastUpdate = mClock.restart();
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      // DO SOMETHING
      Message tick(Message::LogicTick);
      mMessageBus->post(&tick);
    }
  }
}

void Game::notify(Message* msg) {
  if (msg->type == Message::Quit) {
    mQuitFlag = true;
  }
}
