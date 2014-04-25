#include <Game.hpp>
#include <MessageBus.hpp>
#define BOOST_TEST_MODULE Test_Game
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>


using namespace boost::unit_test;

class QuitListener : public Listener {
public:
  QuitListener(MessageBus* bus) : Listener(bus), mFail(false){}

  void notify(Message* msg) {
    if (!mFail && msg->type == Message::LogicTick) {
      Message msgQuit(Message::Quit);
      mMessageBus->post(&msgQuit);
    }
  }

  // To make a fail test case
  bool mFail;
};

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
  monitor.p_timeout.set(5);
  monitor.execute(&test_game_2);
}

