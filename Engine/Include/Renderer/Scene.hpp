/**
   This file contains the Scene class.
 */
#ifndef __SCENE_H__
#define __SCENE_H__

#include <SFML/Graphics.hpp>

#include <Renderer/SFMLNode.hpp>

class Scene : private sf::NonCopyable {
  /**
     Each Scene contains a SFMLNode that is to be rendered on screen
     in a View.
   */
public:
  explicit Scene(sf::RenderWindow* window) :
    mWindow(window),
    mSceneView(window->getDefaultView()),
    mSceneGraph(){}
  virtual ~Scene() {}
  // Modifiers
  void setWindow(sf::RenderWindow* _window) {mWindow = _window;}

  // Updates
  virtual void update(float dT) {assert(dT>0.f); mSceneGraph.update(dT);}
  virtual void draw() {
    if (mWindow != nullptr) {
      mWindow->setView(mSceneView);
      mWindow->draw(mSceneGraph);
    }
  }
  virtual void buildScene() {}

protected:
  sf::RenderWindow* mWindow;
  sf::View mSceneView;
  SFMLNode mSceneGraph;
};

#endif // __SCENE_H__
