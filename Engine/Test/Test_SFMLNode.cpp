#define BOOST_TEST_MODULE Test_SFMLNode
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>

#include <SFML/Graphics.hpp>
#include "Test_SFMLNode.hpp"
#include <iostream>
using namespace boost::unit_test;


int test_Draw() {
  sf::RenderWindow target;
  sf::RenderStates states;
  TestSFMLNode* scene = new TestSFMLNode(); // 1

  TestSFMLNode* c1Node = new TestSFMLNode();
  TestSFMLNode* c2Node = new TestSFMLNode();

  TestSFMLNode* c11Node = new TestSFMLNode();
  TestSFMLNode* c21Node = new TestSFMLNode();
  TestSFMLNode* c22Node = new TestSFMLNode();

  TestSFMLNode* c223Node = new TestSFMLNode();

  SceneNode::Ptr c1(c1Node);
  SceneNode::Ptr c2(c2Node);

  SceneNode::Ptr c11(c11Node);
  SceneNode::Ptr c21(c21Node);
  SceneNode::Ptr c22(c22Node);

  SceneNode::Ptr c223(c223Node);

  scene->attachChild(std::move(c1)); // 2
  scene->attachChild(std::move(c2)); // 3

  c1Node->attachChild(std::move(c11));		// 4
  c2Node->attachChild(std::move(c21));		
  c2Node->attachChild(std::move(c22));		// 5

  c22Node->attachChild(std::move(c223));	// 6

  c21 = c2Node->detachChild(*c21Node);

  scene->draw(target, states);
  BOOST_CHECK(drawnCount::count == 6);

  //TestSFMLNode::Destroy(c21);
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
