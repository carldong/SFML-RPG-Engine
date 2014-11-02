#include <vector>
#include <map>

#include <DNA/DNAProp.hpp>

/**
   @brief: Platform independant map data
 */
class MapData {
public:
  typedef std::vector<std::vector<std::map<DNAProp, DNAProp> > > property_type;
  typedef std::vector<DNAProp> tileset_type;

public:
  MapData();
  
private:
  tileset_type tilesets;
  property_type properties;
};
