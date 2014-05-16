#include <Renderer/SFMLNode.hpp>

/**
   The main draw function
 */
void SFMLNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  states.transform *= getTransform();
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
  for (const Ptr& child : getChildren()) {
    static_cast<SFMLNode*>(child.get())->draw(target, states);
  }
}
