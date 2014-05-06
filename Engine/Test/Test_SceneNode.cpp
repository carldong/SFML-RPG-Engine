#define BOOST_TEST_MODULE Test_SceneNode
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>

#include <Renderer/SceneNode.hpp>
#include "Test_SceneNode.hpp"
using namespace boost::unit_test;

void TestSceneNode::updateCurrent(float dT) {
  updated = true;
}

int test_construct() {
  TestSceneNode* scene = new TestSceneNode();

  SceneNode* c1Node = new TestSceneNode();
  SceneNode* c2Node = new TestSceneNode();

  SceneNode* c11Node = new TestSceneNode();
  SceneNode* c21Node = new TestSceneNode();
  SceneNode* c22Node = new TestSceneNode();

  SceneNode* c223Node = new TestSceneNode();

  SceneNode::Ptr c1(c1Node);
  SceneNode::Ptr c2(c2Node);

  SceneNode::Ptr c11(c11Node);
  SceneNode::Ptr c21(c21Node);
  SceneNode::Ptr c22(c22Node);

  SceneNode::Ptr c223(c223Node);

  scene->attachChild(std::move(c1));
  scene->attachChild(std::move(c2));

  c1Node->attachChild(std::move(c11));
  c2Node->attachChild(std::move(c21));
  c2Node->attachChild(std::move(c22));

  c22Node->attachChild(std::move(c223));

  c21 = c2Node->detachChild(*c21Node);
  c1Node->attachChild(std::move(c21));
  c2Node->detachChild(*c22Node);
  //TestSceneNode::Destroy(c22);

  delete scene;

  return 0;
}

int test_Update() {
  TestSceneNode* scene = new TestSceneNode();

  SceneNode* c1Node = new TestSceneNode();
  SceneNode* c2Node = new TestSceneNode();

  SceneNode* c11Node = new TestSceneNode();
  SceneNode* c21Node = new TestSceneNode();
  SceneNode* c22Node = new TestSceneNode();

  SceneNode* c223Node = new TestSceneNode();

  SceneNode::Ptr c1(c1Node);
  SceneNode::Ptr c2(c2Node);

  SceneNode::Ptr c11(c11Node);
  SceneNode::Ptr c21(c21Node);
  SceneNode::Ptr c22(c22Node);

  SceneNode::Ptr c223(c223Node);

  scene->attachChild(std::move(c1));
  scene->attachChild(std::move(c2));

  c1Node->attachChild(std::move(c11));
  c2Node->attachChild(std::move(c21));
  c2Node->attachChild(std::move(c22));

  c22Node->attachChild(std::move(c223));

  c21 = c2Node->detachChild(*c21Node);

  scene->update(0.1f);

  BOOST_CHECK(static_cast<TestSceneNode*>(scene)->updated);
  BOOST_CHECK(static_cast<TestSceneNode*>(c1Node)->updated);
  BOOST_CHECK(static_cast<TestSceneNode*>(c2Node)->updated);
  BOOST_CHECK(static_cast<TestSceneNode*>(c11Node)->updated);
  BOOST_CHECK(!static_cast<TestSceneNode*>(c21Node)->updated);
  BOOST_CHECK(static_cast<TestSceneNode*>(c22Node)->updated);
  BOOST_CHECK(static_cast<TestSceneNode*>(c223Node)->updated);

  //TestSceneNode::Destroy(c21);
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
