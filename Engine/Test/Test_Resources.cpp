#define BOOST_TEST_MODULE Test_Resources
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>
using namespace boost::unit_test;

#include "Test_Resources.hpp"

int test_construct_add() {
  TextureHolder tex_holder;

  tex_holder.load(0, "Test/assets/test_texture.png");

  sf::Texture tex = tex_holder.get(0);
  const sf::Texture ctex = tex_holder.get(0);
  return 0;
}

BOOST_AUTO_TEST_SUITE(Test_Resources)

unit_test_monitor_t& monitor = unit_test_monitor_t::instance();

BOOST_AUTO_TEST_CASE(Test_Construct_Add) {
  monitor.p_timeout.set(3);
  monitor.execute(&test_construct_add);
}

BOOST_AUTO_TEST_SUITE_END()
