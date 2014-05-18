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
  //typedef SceneNode* Ptr;
  typedef std::unique_ptr<SceneNode> Ptr;
  typedef std::vector<Ptr> Container;

public:
  // Class Methods
  //static void Destroy(SceneNode* node);

  // Constructor and destructor
  SceneNode();

public:
  void attachChild(Ptr child);
  Ptr detachChild(const SceneNode& node);
  virtual void update(float dT);

protected:
  Container& getChildren() {return mChildren;}
  const Container& getChildren() const {return mChildren;}
  SceneNode* getParent() {return mParent;}
  const SceneNode* getParent() const {return mParent;}

private:
  virtual void updateCurrent(float dT);
  virtual void updateChildren(float dT);


  //private:
protected:
  Container mChildren;
  SceneNode* mParent;
  //static Container sNodes;
};

#endif // __SCENENODE_H__
