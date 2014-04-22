#include <MessageBus.hpp>
#include <Game.hpp>

int main() {
  MessageBus* messageBus = new MessageBus;
  Game game(messageBus);
  game.run();
  delete messageBus;
}
