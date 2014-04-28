#include <MessageBus.hpp>
#define BOOST_TEST_MODULE Test_MessageBus
#include <boost/test/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>

#include <memory>

using namespace boost::unit_test;

class Test_Listener : public Listener {
public:
  Test_Listener(MessageBus* bus) : Listener(bus) {}
  void notify(Message* msg) {
    mMessages.push_back(msg);
  }
public:
  std::vector<Message*> mMessages;
};

int test_messagebus_method() {
  MessageBus* bus = new MessageBus;
  
  Test_Listener* l1 = new Test_Listener(bus);
  Test_Listener* l2 = new Test_Listener(bus);

  Message* msg1 = new Message(Message::Pause);
  Message* msg2 = new RichMessage<int>(Message::Rich, 0);
  Message* msg3 = new Message(Message::LogicTick);

  BOOST_CHECK(msg1->type == Message::Pause);
  BOOST_CHECK(msg2->type == Message::Rich &&
	      static_cast<RichMessage<int>*>(msg2)->value == 0);
  BOOST_CHECK(msg3->type == Message::LogicTick);

  bus->post(msg1);
  bus->post(msg2);
  bus->post(msg3);

  BOOST_CHECK(l1->mMessages[0] == msg1);
  BOOST_CHECK(l1->mMessages[1] == msg2);
  BOOST_CHECK(l1->mMessages[2] == msg3);
  BOOST_CHECK(l2->mMessages[0] == msg1);
  BOOST_CHECK(l2->mMessages[1] == msg2);
  BOOST_CHECK(l2->mMessages[2] == msg3);
  
  delete bus;
  return 0;
}

BOOST_AUTO_TEST_CASE(test_messagebus) {
  unit_test_monitor_t& monitor = unit_test_monitor_t::instance();
  monitor.p_timeout.set(1);
  monitor.execute(&test_messagebus_method);
}

