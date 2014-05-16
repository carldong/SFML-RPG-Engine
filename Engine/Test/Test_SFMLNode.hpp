#ifndef __TEST_SFML_NODE_H__
#define __TEST_SFML_NODE_H__

#include <Renderer/SFMLNode.hpp>

struct drawnCount {
  drawnCount() {count++;}
  static int count;
};

int drawnCount::count = 0;

class TestSFMLNode : public SFMLNode {
public:
  using SFMLNode::draw;
  void drawCurrent(sf::RenderTarget& target,
		   sf::RenderStates states) const {
    drawnCount();
  }
};

#endif // __TEST_SFML_NODE_H__
