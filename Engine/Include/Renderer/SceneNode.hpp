#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include <set>
#include <cassert>
#include <memory>
#include <algorithm>

/**
   Base class of Scene Nodes
 */
class SceneNode {
public:
  typedef SceneNode* Ptr;

public:
  // Class Methods
  static void Destroy(SceneNode* node);

  // Constructor and destructor
  SceneNode();
  ~SceneNode();

public:
  void attachChild(Ptr child);
  Ptr detachChild(SceneNode* node);
  virtual void update(float dT);
  virtual void updateCurrent(float dT);
  void updateChildren(float dT);


protected:
  std::set<Ptr> mChildren;
  SceneNode* mParent;
  static std::set<Ptr> sNodes;
};

#endif // __SCENENODE_H__
