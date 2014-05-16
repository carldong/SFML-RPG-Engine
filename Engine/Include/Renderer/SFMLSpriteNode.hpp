#ifndef __SFML_SPRITE_NODE_H__
#define __SFML_SPRITE_NODE_H__

#include "SceneNode.hpp"

class SFMLSpriteNode : public SFMLNode {
public:
  explicit SFMLSpriteNode(const sf::Texture& texture);
  SFMLSpriteNode(const sf::Texture& _texture,
                 const sf::IntRect& rect);

private:
  virtual void drawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const;

private:
  sf::Sprite mSprite;
};

#endif // __SFML_SPRITE_NODE_H__
