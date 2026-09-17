#pragma once

#include "RNOH/ArkTSMessageHub.h"
#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/CustomNode.h"
#include "RNOH/generated/components/BaseKeyboardInsetsViewComponentInstance.h"

namespace rnoh {

class KeyboardInsetsViewComponentInstance final
    : public BaseKeyboardInsetsViewComponentInstance,
      public ArkTSMessageHub::Observer {
 public:
  KeyboardInsetsViewComponentInstance(Context context);

  void onChildInserted(ComponentInstance::Shared const& childComponentInstance,
                       std::size_t index) override;
  void onChildRemoved(
      ComponentInstance::Shared const& childComponentInstance) override;
  CustomNode& getLocalRootArkUINode() override;

  void onMessageReceived(ArkTSMessage const& message) override;

 private:
  CustomNode m_customNode;
  float m_lastPosition = 0;
  float m_lastHeight = 0;
  bool m_lastShown = false;
  bool m_lastTransitioning = false;
  bool m_hasKeyboardState = false;
};

} // namespace rnoh
