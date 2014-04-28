#define BOOST_TEST_MODULE Test_Game
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>

#include "Test_Game.hpp"

using namespace boost::unit_test;

int test_game_1() {
  MessageBus* bus = new MessageBus;
  Game* game = new Game(bus);
  QuitListener* quitListener = new QuitListener(bus);
  game->run();

  delete bus;

  return 0;
}


BOOST_AUTO_TEST_CASE(Test_Game_Success) {
  unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
  monitor.p_timeout.set(5);
  monitor.execute(&test_game_1);
}


