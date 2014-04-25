#ifndef __SCENENODE_H__
#define __SCENENODE_H__

#include <set>
#include <cassert>
#include <memory>
#include <algorithm>

class SceneNode {
public:
  typedef SceneNode* Ptr;

public:
  SceneNode();
  ~SceneNode();
  static void Destroy(SceneNode* node);
  
public:

  void attachChild(Ptr child);
  Ptr detachChild(SceneNode* node);
  virtual void update(float dT) {assert(dT>0.f);updateChildren(dT);}

protected:
  virtual void updateChildren(float dT);

protected:
  std::set<Ptr> mChildren;
  SceneNode* mParent;
  static std::set<Ptr> sNodes;
};

#endif // __SCENENODE_H__
