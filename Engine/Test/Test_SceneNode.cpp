#define BOOST_TEST_MODULE Test_SceneNode
#include <boost/test/included/unit_test.hpp>
#include <boost/test/unit_test_monitor.hpp>
#include <boost/bind.hpp>

#include <Renderer/SceneNode.hpp>

using namespace boost::unit_test;


int test_construct() {
  SceneNode* scene = new SceneNode();

  SceneNode* c1 = new SceneNode();
  SceneNode* c2 = new SceneNode();

  SceneNode* c11 = new SceneNode();
  SceneNode* c21 = new SceneNode();
  SceneNode* c22 = new SceneNode();

  SceneNode* c223 = new SceneNode();

  scene->attachChild(c1);
  scene->attachChild(c2);

  c1->attachChild(c11);
  c2->attachChild(c21);
  c2->attachChild(c22);

  c22->attachChild(c223);

  c2->detachChild(c21);
  SceneNode::Destroy(c21);
  c2->detachChild(c22);
  SceneNode::Destroy(c22);

  delete scene;

  return 0;
}

int test_Update() {
  SceneNode* scene = new SceneNode();

  SceneNode* c1 = new SceneNode();
  SceneNode* c2 = new SceneNode();

  SceneNode* c11 = new SceneNode();
  SceneNode* c21 = new SceneNode();
  SceneNode* c22 = new SceneNode();

  SceneNode* c223 = new SceneNode();

  scene->attachChild(c1);
  scene->attachChild(c2);

  c1->attachChild(c11);
  c2->attachChild(c21);
  c2->attachChild(c22);

  c22->attachChild(c223);

  c2->detachChild(c21);
  SceneNode::Destroy(c21);

  scene->update(0.1f);

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
