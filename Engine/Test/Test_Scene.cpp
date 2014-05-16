#define BOOST_TEST_MODULE Test_SceneNode
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>
using namespace boost::unit_test;

#include "Test_Scene.hpp"

int test_construct() {
  sf::RenderWindow window;
  TestScene scene(&window);
  
  return 0;
}

BOOST_AUTO_TEST_SUITE(Test_Scene)
unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
	  
BOOST_AUTO_TEST_CASE(Test_Construct) {
  monitor.p_timeout.set(3);
  monitor.execute(&test_construct);
}

BOOST_AUTO_TEST_SUITE_END()
