#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <memory>
#include <cassert>
#include <iostream>
#include <map>

#include <SFML/Graphics.hpp>

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
  void load(Identifier id, const std::string& filename);
  template<typename Parameter> void load(Identifier id,
					 const std::string& filename,
					 const Parameter& secondParam);
  
  Resource& get(Identifier id);
  const Resource& get(Identifier id) const;
  
private:
  std::map<Identifier, std::unique_ptr<Resource> > mResourceMap;
};

typedef ResourceHolder<sf::Texture, size_t> TextureHolder;

#include "Resources_impl.hpp"
#endif  //__TEXTURE_H__
