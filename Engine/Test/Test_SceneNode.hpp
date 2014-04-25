#ifndef __TEST_SCENE_NODE_H__
#define __TEST_SCENE_NODE_H__

class TestSceneNode : public SceneNode {
public:
  TestSceneNode() : SceneNode(), updated(false) {}
  void updateCurrent(float dT);
public:
  bool updated;
};

#endif // __TEST_SCENE_NODE_H__
