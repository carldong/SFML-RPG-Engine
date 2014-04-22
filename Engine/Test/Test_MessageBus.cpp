#include "MessageBus.hpp"
#define BOOST_TEST_MODULE Test_MessageBus
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_messagebus) {
  MessageBus* bus = new MessageBus;
  delete bus;
}
