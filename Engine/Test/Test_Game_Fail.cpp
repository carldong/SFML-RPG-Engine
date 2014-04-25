#define BOOST_TEST_MODULE Test_Game
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>

#include "Test_Game.hpp"

using namespace boost::unit_test;


int test_game_2() {
  MessageBus* bus = new MessageBus;
  Game game(bus);
  QuitListener quitListener(bus);
  quitListener.mFail = true;
  
  game.run();

  delete bus;
  
  return 0;
}

BOOST_AUTO_TEST_CASE_EXPECTED_FAILURES(Test_Game_Fail, 1)
BOOST_AUTO_TEST_CASE(Test_Game_Fail)
{
  unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
  monitor.p_timeout.set(3);
  monitor.execute(&test_game_2);
}

