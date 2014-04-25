#define BOOST_TEST_MODULE Test_SFMLNode
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>

#include <SFML/Graphics.hpp>
#include "Test_SFMLNode.hpp"
#include <iostream>
using namespace boost::unit_test;

struct drawnCount {
  drawnCount() {count++;}
  static int count;
};

int drawnCount::count = 0;

void TestSFMLNode::drawCurrent(sf::RenderTarget& target,
			 sf::RenderStates states) const {
  drawnCount();
}


int test_Draw() {
  sf::RenderWindow target;
  sf::RenderStates states;
  TestSFMLNode* scene = new TestSFMLNode(); // 1

  TestSFMLNode* c1 = new TestSFMLNode();
  TestSFMLNode* c2 = new TestSFMLNode();

  TestSFMLNode* c11 = new TestSFMLNode();
  TestSFMLNode* c21 = new TestSFMLNode();
  TestSFMLNode* c22 = new TestSFMLNode();

  TestSFMLNode* c223 = new TestSFMLNode();

  scene->attachChild(c1); // 2
  scene->attachChild(c2); // 3

  c1->attachChild(c11);		// 4
  c2->attachChild(c21);		
  c2->attachChild(c22);		// 5

  c22->attachChild(c223);	// 6

  c2->detachChild(c21);

  scene->draw(target, states);
  std::cout << "[DEBUG]Test_SFMLNode.cpp " << drawnCount::count << std::endl;
  BOOST_CHECK(drawnCount::count == 6);

  TestSFMLNode::Destroy(c21);
  delete scene;

  return 0;
}

BOOST_AUTO_TEST_SUITE(Test_SFMLNode)
unit_test_monitor_t& monitor = unit_test_monitor_t::instance();

BOOST_AUTO_TEST_CASE(Test_Draw) {
  monitor.p_timeout.set(3);
  monitor.execute(&test_Draw);
}

BOOST_AUTO_TEST_SUITE_END()
