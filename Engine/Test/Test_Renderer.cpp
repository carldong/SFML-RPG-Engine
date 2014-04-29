#define BOOST_TEST_MODULE Test_Renderer
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>
using namespace boost::unit_test;

#include "Test_Renderer.hpp"

int test_Renderer_construct() {
  MessageBus* pMessageBus = new MessageBus();
  Game* pGame = new TestGame(pMessageBus);
  Renderer* pRenderer = new Renderer(pMessageBus,
                                     640, 480, "Test Renderer Construct");

  pGame->run();
  
  delete pRenderer;
  delete pGame;
  delete pMessageBus;
  
  return 0;
}

BOOST_AUTO_TEST_SUITE(Test_Renderer)
unit_test_monitor_t& monitor = unit_test_monitor_t::instance();

BOOST_AUTO_TEST_CASE(Test_Construct) {
  monitor.p_timeout.set(5);
  monitor.execute(&test_Renderer_construct);
}


BOOST_AUTO_TEST_SUITE_END()
