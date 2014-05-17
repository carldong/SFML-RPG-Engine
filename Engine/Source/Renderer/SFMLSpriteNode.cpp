#include <Renderer/SFMLSpriteNode.hpp>

SFMLSpriteNode::SFMLSpriteNode(const sf::Texture& _texture) :
  SFMLNode(), mSprite(_texture) {}

SFMLSpriteNode::SFMLSpriteNode(const sf::Texture& _texture,
                               const sf::IntRect& _rect) :
  SFMLNode(), mSprite(_texture, _rect){}

void SFMLSpriteNode::drawCurrent(sf::RenderTarget& target,
                                 sf::RenderStates states) const 
{
  target.draw(mSprite, states);
}

