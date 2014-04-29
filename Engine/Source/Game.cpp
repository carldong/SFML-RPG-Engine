#include <Game.hpp>

Game::Game(MessageBus* bus) : Listener(bus){
  mMessageBus = bus;
  mQuitFlag = false;
  registerTo(bus);
}

/**
   The main game loop. Sends LogicTick message after interval to drive
   MessageBus
 */
void Game::run() {
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  mClock.restart();
  while (!mQuitFlag) {
    timeSinceLastUpdate += mClock.restart();
    while (timeSinceLastUpdate > TimePerFrame) {
      timeSinceLastUpdate -= TimePerFrame;
      // DO SOMETHING
      Message* tick = new Message(Message::LogicTick);
      mMessageBus->post(tick);
    }
  }
}

void Game::notify(Message* msg) {
  if (msg->type == Message::Quit) {
    mQuitFlag = true;
  }
}
