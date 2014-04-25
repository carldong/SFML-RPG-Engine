#define BOOST_TEST_MODULE Test_SceneNode
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>

#include <Renderer/SceneNode.hpp>
#include "Test_SceneNode.hpp"
using namespace boost::unit_test;

void TestSceneNode::update(float dT) {
  updateChildren(dT);
  updated = true;
}

int test_construct() {
  TestSceneNode* scene = new TestSceneNode();

  TestSceneNode* c1 = new TestSceneNode();
  TestSceneNode* c2 = new TestSceneNode();

  TestSceneNode* c11 = new TestSceneNode();
  TestSceneNode* c21 = new TestSceneNode();
  TestSceneNode* c22 = new TestSceneNode();

  TestSceneNode* c223 = new TestSceneNode();

  scene->attachChild(c1);
  scene->attachChild(c2);

  c1->attachChild(c11);
  c2->attachChild(c21);
  c2->attachChild(c22);

  c22->attachChild(c223);

  c2->detachChild(c21);
  TestSceneNode::Destroy(c21);
  c2->detachChild(c22);
  TestSceneNode::Destroy(c22);

  delete scene;

  return 0;
}

int test_Update() {
  TestSceneNode* scene = new TestSceneNode();

  TestSceneNode* c1 = new TestSceneNode();
  TestSceneNode* c2 = new TestSceneNode();

  TestSceneNode* c11 = new TestSceneNode();
  TestSceneNode* c21 = new TestSceneNode();
  TestSceneNode* c22 = new TestSceneNode();

  TestSceneNode* c223 = new TestSceneNode();

  scene->attachChild(c1);
  scene->attachChild(c2);

  c1->attachChild(c11);
  c2->attachChild(c21);
  c2->attachChild(c22);

  c22->attachChild(c223);

  c2->detachChild(c21);

  scene->update(0.1f);

  BOOST_CHECK(scene->updated);
  BOOST_CHECK(c1->updated);
  BOOST_CHECK(c2->updated);
  BOOST_CHECK(c11->updated);
  BOOST_CHECK(!c21->updated);
  BOOST_CHECK(c22->updated);
  BOOST_CHECK(c223->updated);

  TestSceneNode::Destroy(c21);
  delete scene;

  return 0;
}

BOOST_AUTO_TEST_SUITE(Test_SceneNode_Success)
unit_test_monitor_t& monitor = unit_test_monitor_t::instance();

BOOST_AUTO_TEST_CASE(Test_Construct) {
  monitor.p_timeout.set(3);
  monitor.execute(&test_construct);
}

BOOST_AUTO_TEST_CASE(Test_Update) {
  monitor.p_timeout.set(3);
  monitor.execute(&test_Update);
}

BOOST_AUTO_TEST_SUITE_END()
