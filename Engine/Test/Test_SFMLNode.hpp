#ifndef __TEST_SFML_NODE_H__
#define __TEST_SFML_NODE_H__

#include <Renderer/SFMLNode.hpp>

class TestSFMLNode : public SFMLNode {
public:
  void drawCurrent(sf::RenderTarget& target,
		   sf::RenderStates states) const;
};

#endif // __TEST_SFML_NODE_H__
