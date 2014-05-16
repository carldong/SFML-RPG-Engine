#include <Renderer/SFMLSpriteNode.hpp>

SFMLSpriteNode::SpriteNode(const sf::Texture& texture) :
  mSprite(texture) {}

SFMLSpriteNode::SFMLSpriteNode(const sf::Texture& _texture,
                               const sf::IntRect& rect) {}

void SpriteNode::drawCurrent(sf::RenderTarget& target,
                             sf::RenderStates states) const 
{
  target.draw(mSprite, states);
}

