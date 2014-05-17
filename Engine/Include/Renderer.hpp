#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <memory>

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <MessageBus.hpp>
#include <Renderer/SceneNode.hpp>
#include <Renderer/SFMLSpriteNode.hpp>
#include <Renderer/Scene.hpp>

/**
   This is the Listener to actually render graphics.
 */
class Renderer : public Listener {
public:
  typedef std::unique_ptr<Scene> Ptr;
  
public:
  Renderer(MessageBus* bus,
           unsigned int width, unsigned int height,
	   const std::string& title);
  // Accessors
  Scene* getScene() {return mScene.get();}

  // Modifiers
  Ptr setScene(Ptr _scene);

  // Events
  void processEvents();
  // Listeners
  void update();
  void notify(Message* msg);

private:
void render();

private:
  sf::RenderWindow mWindow;
  sf::Clock mClock;
  Ptr mScene;
  bool mReady;
bool mIsClosed;
};

#endif // __RENDERER_H__
