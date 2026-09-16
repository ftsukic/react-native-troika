#pragma once

#include "RNOH/CppComponentInstance.h"
#include "RNOH/arkui/CustomNode.h"
#include "RNOH/generated/components/BaseKeyboardInsetsViewComponentInstance.h"

namespace rnoh {

class KeyboardInsetsViewComponentInstance final
    : public BaseKeyboardInsetsViewComponentInstance {
 public:
  KeyboardInsetsViewComponentInstance(Context context);

  void onChildInserted(ComponentInstance::Shared const& childComponentInstance,
                       std::size_t index) override;
  void onChildRemoved(
      ComponentInstance::Shared const& childComponentInstance) override;
  CustomNode& getLocalRootArkUINode() override;

 private:
  CustomNode m_customNode;
};

} // namespace rnoh
