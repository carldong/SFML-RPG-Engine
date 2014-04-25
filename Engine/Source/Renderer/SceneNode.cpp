#include <Renderer/SceneNode.hpp>

std::set<SceneNode::Ptr> SceneNode::sNodes;

void SceneNode::Destroy(SceneNode* node) {
  size_t result = sNodes.erase(node);
  assert (result != 0);
  delete node;
}

SceneNode::SceneNode() : mChildren(), mParent(nullptr) {
  sNodes.insert(this);
}

SceneNode::~SceneNode() {
  for (std::set<Ptr>::iterator child=mChildren.begin();
       child!=mChildren.end(); ++child) {
    delete *child;
  }
}

void SceneNode::attachChild(Ptr child) {
  assert (child != nullptr);
  child->mParent = this;
  mChildren.insert(child);
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
  for (std::set<Ptr>::iterator child=mChildren.begin();
       child!=mChildren.end(); ++child) {
    (*child)->update(dT);
  }
}
