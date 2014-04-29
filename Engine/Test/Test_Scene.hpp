#ifndef __TEST_SCENE_H__
#define __TEST_SCENE_H__

#include <Renderer/Scene.hpp>

class TestScene : public Scene {
public:
  explicit TestScene(sf::RenderWindow* window) :
    Scene(window) {}
  void buildScene() {}
};

#endif // __TEST_SCENE_H__
