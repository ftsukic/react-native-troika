#include "KeyboardInsetsViewComponentInstance.h"

#include <utility>

namespace rnoh {

KeyboardInsetsViewComponentInstance::KeyboardInsetsViewComponentInstance(
    Context context)
    : BaseKeyboardInsetsViewComponentInstance(std::move(context)),
      m_customNode(m_arkUINodeCtx) {}

void KeyboardInsetsViewComponentInstance::onChildInserted(
    ComponentInstance::Shared const& childComponentInstance,
    std::size_t index) {
  CppComponentInstance::onChildInserted(childComponentInstance, index);
  m_customNode.insertChild(
      childComponentInstance->getLocalRootArkUINode(), index);
}

void KeyboardInsetsViewComponentInstance::onChildRemoved(
    ComponentInstance::Shared const& childComponentInstance) {
  CppComponentInstance::onChildRemoved(childComponentInstance);
  m_customNode.removeChild(childComponentInstance->getLocalRootArkUINode());
}

CustomNode& KeyboardInsetsViewComponentInstance::getLocalRootArkUINode() {
  return m_customNode;
}

} // namespace rnoh
