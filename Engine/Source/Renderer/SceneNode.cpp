#include <Renderer/SceneNode.hpp>

std::set<SceneNode::Ptr> SceneNode::sNodes;

void SceneNode::Destroy(SceneNode* node) {
  assert (node->mParent == nullptr);
  size_t result = sNodes.erase(node);
  assert (result != 0);
  delete node;
}

SceneNode::SceneNode() : mChildren(), mParent(nullptr) {
  sNodes.insert(this);
}

SceneNode::~SceneNode() {
  for (SceneNode* child : mChildren) {
    delete child;
  }
}

void SceneNode::attachChild(Ptr child) {
  assert (child != nullptr);
  child->mParent = this;
  bool success = mChildren.insert(child).second;
  assert (success);
}

SceneNode::Ptr SceneNode::detachChild(SceneNode* node) {
  std::set<Ptr>::iterator found = mChildren.find(node);
  assert (found != mChildren.end());

  Ptr result(*found);
  result->mParent = nullptr;
  mChildren.erase(found);
  return result;
}

void SceneNode::updateChildren(float dT) {
  assert (dT > 0.f);
  for (SceneNode* child : mChildren) {
    child->update(dT);
  }
}
