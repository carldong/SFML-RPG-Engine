#include <Renderer/SFMLNode.hpp>

/**
   The main draw function
 */
void SFMLNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  drawCurrent(target, states);
  drawChildren(target, states);
}

/**
   Draw current SFMLNode
 */
void SFMLNode::drawCurrent(sf::RenderTarget& target,
			   sf::RenderStates states) const {
}

/**
   Draw all children
 */
void SFMLNode::drawChildren(sf::RenderTarget& target,
			   sf::RenderStates states) const {
  for (SceneNode* child : mChildren) {
    static_cast<SFMLNode*>(child)->draw(target, states);
  }
}
