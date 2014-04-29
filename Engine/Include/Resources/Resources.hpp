#ifndef __RESOURCES_H__
#define __RESOURCES_H__

#include <SFML/System.hpp>
#include <memory>
#include <cassert>
#include <map>

template<typename Resource, typename Identifier>
class ResourceHolder {
public:
  void load(Identifier id, const std::string& filename);

  template<typename Parameter>
  void load(Identifier id, const std::string& filename,
            const Parameter& secondParam);

  Resource& get(Identifier id);
  const Resource& get(Identifier id) const;

private:
  std::map<Identifier, std::unique_ptr<Resource> > mResourceMap;
};

#include "Resources_impl.hpp"
#endif // __RESOURCES_H__
