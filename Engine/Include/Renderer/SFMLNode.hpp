#ifndef __SFML_NODE_H__
#define __SFML_NODE_H__

#include <Renderer/SceneNode.hpp>
#include <SFML/Graphics.hpp>

/**
   SceneNode for SFML engine
 */
class SFMLNode : public SceneNode ,
		 public sf::Transformable,
		 public sf::Drawable,
		 public sf::NonCopyable {
public:
  SFMLNode() : SceneNode() {}
  virtual ~SFMLNode() {}
  //protected:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

private:
  virtual void drawCurrent(sf::RenderTarget& target,
			   sf::RenderStates states) const;
  virtual void drawChildren(sf::RenderTarget& target,
			    sf::RenderStates states) const;

};

#endif // __SFML_NODE_H__
