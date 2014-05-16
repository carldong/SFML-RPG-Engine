#ifndef __TEST_RESOURCES_H__
#define __TEST_RESOURCES_H__

#include <Resources/Resources.hpp>
#include <SFMl/Graphics.hpp>

int test_construct_add() {
  return 0;
}

BOOST_AUTO_TEST_SUITE(Test_Resources)
unit_test_monitor_t& monitor = unit_test_monitor_t::instance();

BOOST_AUTO_TEST_CASE(Test_Construct_Add) {
  monitor.p_timeout.set(3);
  monitor.execute(&test_construct_add);
}

BOOST_AUTO_TEST_SUITE_END()

#endif // __TEST_RESOURCES_H__
