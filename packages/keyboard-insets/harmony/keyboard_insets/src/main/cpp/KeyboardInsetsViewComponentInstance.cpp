#include "KeyboardInsetsViewComponentInstance.h"

#include <utility>

namespace rnoh {

KeyboardInsetsViewComponentInstance::KeyboardInsetsViewComponentInstance(
    Context context)
    : BaseKeyboardInsetsViewComponentInstance(std::move(context)),
      ArkTSMessageHub::Observer(m_deps->arkTSMessageHub),
      m_customNode(m_arkUINodeCtx) {}

void KeyboardInsetsViewComponentInstance::onMessageReceived(
    ArkTSMessage const& message) {
  if (message.name != "KeyboardInsets::KeyboardChanged" ||
      !message.payload.isObject() ||
      !message.payload.count("position") ||
      !message.payload.count("height") ||
      !message.payload.count("shown") ||
      !message.payload.count("transitioning") ||
      !message.payload["position"].isNumber() ||
      !message.payload["height"].isNumber() ||
      !message.payload["shown"].isBool() ||
      !message.payload["transitioning"].isBool()) {
    return;
  }

  auto props = std::dynamic_pointer_cast<const facebook::react::KeyboardInsetsViewProps>(
      getProps());
  if (props == nullptr || props->mode != facebook::react::KeyboardInsetsViewMode::Manual) {
    return;
  }

  const float position = static_cast<float>(message.payload["position"].asDouble());
  const float height = static_cast<float>(message.payload["height"].asDouble());
  const bool shown = message.payload["shown"].asBool();
  const bool transitioning = message.payload["transitioning"].asBool();
  const bool positionChanged = !m_hasKeyboardState || position != m_lastPosition;
  const bool statusChanged = !m_hasKeyboardState || height != m_lastHeight ||
      shown != m_lastShown || transitioning != m_lastTransitioning;

  auto eventEmitter = getEventEmitter();
  if (eventEmitter == nullptr) {
    return;
  }
  if (statusChanged) {
    eventEmitter->onStatusChanged({
        .height = height,
        .shown = shown,
        .transitioning = transitioning,
    });
  }
  if (positionChanged) {
    eventEmitter->onPositionChanged({.position = position});
  }

  m_lastPosition = position;
  m_lastHeight = height;
  m_lastShown = shown;
  m_lastTransitioning = transitioning;
  m_hasKeyboardState = true;
}

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
