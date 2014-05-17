#ifndef __SFML_SPRITE_NODE_H__
#define __SFML_SPRITE_NODE_H__

#include <Renderer/SFMLNode.hpp>

class SFMLSpriteNode : public SFMLNode {
public:
  explicit SFMLSpriteNode(const sf::Texture& _texture);
  SFMLSpriteNode(const sf::Texture& _texture,
                 const sf::IntRect& _rect);

private:
  virtual void drawCurrent(sf::RenderTarget& target,
                           sf::RenderStates states) const;

private:
  sf::Sprite mSprite;
};

#endif // __SFML_SPRITE_NODE_H__
