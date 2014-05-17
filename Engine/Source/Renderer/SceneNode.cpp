#include <Renderer/SceneNode.hpp>

#include <iostream>

/**
   Construct a SceneNode, and add the pointer to this object to class
   member variable sNodes
 */
SceneNode::SceneNode() : mChildren(), mParent(nullptr) {
}

/**
   Attaches another sceneNode to this one

   @param child The SceneNode to be added
 */
void SceneNode::attachChild(Ptr child) {
  child->mParent = this;
  //bool success = mChildren.insert(child).second;
  mChildren.push_back(std::move(child));
}

/**
   Detaches a child node

   @param node The SceneNode to be removed
 */
SceneNode::Ptr SceneNode::detachChild(const SceneNode& node) {
  Container::iterator found = 
    std::find_if(mChildren.begin(), mChildren.end(),
                 [&](Ptr& p)->bool {return p.get() == &node;} );
  assert (found != mChildren.end());

  Ptr result = std::move(*found);
  result->mParent = nullptr;
  mChildren.erase(found);
  return result;
}

/**
   Update function

   @param dT Elapsed time
 */
void SceneNode::update(float dT) {
  assert(dT>0.f);
  updateCurrent(dT);
  updateChildren(dT);
}

/**
   Updates this scene node

   @param dT Elapsed time
 */
void SceneNode::updateCurrent(float dT) {
}
					

/**
   Updates child node

   @param dT Elapsed time
 */
void SceneNode::updateChildren(float dT) {
  assert (dT > 0.f);
  for (Ptr& child : mChildren) {
    child->update(dT);
  }
}
