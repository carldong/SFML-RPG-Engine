#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/Graphics.cpp>

#include <Renderer/SFMLNode.hpp>

class Scene : private sf::NonCopyable {
public:
  explicit Scene(sf::RenderWindow& window) :
    mWindow(window), mWorldView(window.getDefaultView()) {}
  virtual void update(float dT) {assert(dT>0.f); mSceneGraph.update(dT);}
  virtual void draw() {mWindow.setView(mSceneView); mWindow.draw(mSceneGraph);}
  virtual void buildScene() {}

protected:

protected:
  sf::RenderWindow& mWindow;
  sf::View mSceneView;
  SFMLNode mSceneGraph;
};

#endif // __SCENE_H__
