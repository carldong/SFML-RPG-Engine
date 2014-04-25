#define BOOST_TEST_MODULE Test_Testsuite
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>


using namespace boost::unit_test;

//____________________________________________________________________________//

int func(){
  BOOST_CHECK(true);
  return 0;
}

int func_fail() {
  while(1);
  return 0;
}

BOOST_AUTO_TEST_CASE(Test_TestSuite_Normal) {
BOOST_CHECK(true);
 unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
 monitor.p_timeout.set(3);
 monitor.execute(func);
}

