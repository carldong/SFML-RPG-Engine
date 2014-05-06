#include <Renderer/SceneNode.hpp>

//std::set<SceneNode::Ptr> SceneNode::sNodes;

/**
   Delete a scene node from memory
 */
/*
void SceneNode::Destroy(SceneNode* node) {
  assert (node->mParent == nullptr);
  size_t result = sNodes.erase(node);
  assert (result != 0);
  delete node;
}
*/

/**
   Construct a SceneNode, and add the pointer to this object to class
   member variable sNodes
 */
SceneNode::SceneNode() : mChildren(), mParent(nullptr) {
  //  sNodes.insert(this);
}

/**
   Destructor of a SceneNode. Deletes all its child.
 */
/*
SceneNode::~SceneNode() {
  for (SceneNode* child : mChildren) {
    delete child;
  }
}
*/

/**
   Attaches another sceneNode to this one

   @param child The SceneNode to be added
 */
void SceneNode::attachChild(Ptr child) {
  assert (child != nullptr);
  child->mParent = this;
  //bool success = mChildren.insert(child).second;
  mChildren.push_back(std::move(child));
}

/**
   Detaches a child node

   @param node The SceneNode to be removed
 */
/*
SceneNode::Ptr SceneNode::detachChild(SceneNode* node) {
  std::set<Ptr>::iterator found = mChildren.find(node);
  assert (found != mChildren.end());

  Ptr result(*found);
  result->mParent = nullptr;
  mChildren.erase(found);
  return result;
}
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
