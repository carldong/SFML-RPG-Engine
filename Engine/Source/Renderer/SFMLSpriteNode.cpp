#include <Renderer/SFMLSpriteNode.hpp>

SFMLSpriteNode::SFMLSpriteNode(const sf::Texture& _texture) :
  mSprite(_texture) {}

SFMLSpriteNode::SFMLSpriteNode(const sf::Texture& _texture,
                               const sf::IntRect& _rect) :
  mSprite(_texture, _rect){}

void SFMLSpriteNode::drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const 
{
  target.draw(mSprite, states);
}

