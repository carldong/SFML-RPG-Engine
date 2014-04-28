#ifndef __RENDERER_H__
#define __RENDERER_H__

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include <MessageBus.hpp>
#include <Renderer/SceneNode.hpp>
#include <Renderer/Scene.hpp>

/**
   This is the Listener to actually render graphics.
 */
class Renderer : public Listener {
public:
  Renderer(unsigned int width, unsigned int height,
	   const std::string& title);

  // Events
  void processEvents();
  // Listeners
  void update();
  void notify(Message* msg);
  
private:
  sf::RenderWindow mWindow;
  sf::Clock mClock;
};

#endif // __RENDERER_H__
