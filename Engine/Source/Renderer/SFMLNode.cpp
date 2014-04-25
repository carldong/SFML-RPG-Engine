#include <Renderer/SFMLNode.hpp>

void SFMLNode::draw(sf::RenderTarget& target, sf::RenderStates states) const {
  drawCurrent(target, states);
  drawChildren(target, states);
}

void SFMLNode::drawCurrent(sf::RenderTarget& target,
			   sf::RenderStates states) const {
}

void SFMLNode::drawChildren(sf::RenderTarget& target,
			   sf::RenderStates states) const {
  for (std::set<Ptr>::iterator child=mChildren.begin();
       child!=mChildren.end(); ++child) {
    static_cast<SFMLNode*>(*child)->draw(target, states);
  }
}
