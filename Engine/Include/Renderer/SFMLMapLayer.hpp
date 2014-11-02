#include <SFML/Graphics.hpp>
#include <Renderer/SFMLNode.hpp>

class SFMLMapLayer : public SFMLNode {
public:
  SFMLMapLayer();
  ~SFMLMapLayer();

public:
  void update(float dT);
  void draw(sf::RenderTarget& target, sf::RenderStates states) const;

protected:

private:
  void drawCurrent(sf::RenderTarget& target,
		   sf::RenderStates states) const;
  void drawChildren(sf::RenderTarget& target,
		    sf::RenderStates states) const;
  
private:
  Ptr mData;
};

