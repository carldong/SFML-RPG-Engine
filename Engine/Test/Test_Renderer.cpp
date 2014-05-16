#define BOOST_TEST_MODULE Test_Renderer
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>
using namespace boost::unit_test;

#include "Test_Renderer.hpp"

int test_Renderer_construct() {
  MessageBus bus;
  TestGame game(&bus);
  Renderer renderer(&bus,
                     640, 480, "Test Renderer Construct");

  game.run();
  
  return 0;
}

int test_Renderer_scene1() {
  MessageBus bus;
  TestGame game(&bus);
  Renderer renderer(&bus,
                    640, 480, "Test Renderer Scene 1");
  

  return 0;
}

BOOST_AUTO_TEST_SUITE(Test_Renderer)
unit_test_monitor_t& monitor = unit_test_monitor_t::instance();

BOOST_AUTO_TEST_CASE(Test_Construct) {
  monitor.p_timeout.set(5);
  monitor.execute(&test_Renderer_construct);
}


BOOST_AUTO_TEST_SUITE_END()
