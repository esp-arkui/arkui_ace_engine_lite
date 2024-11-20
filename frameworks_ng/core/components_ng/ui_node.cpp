#include "ui_node.h"

namespace OHOS{
namespace ACELite {
thread_local int64_t currentAccessibilityId_ = 0;
UINode::UINode(const std::string& tag, int32_t nodeId, bool isRoot)
    : tag_(tag), nodeId_(nodeId), accessibilityId_(currentAccessibilityId_++), isRoot_(isRoot)
{
    printf("UINode::UINode------\n");
}

UINode::~UINode()
{
    printf("UINode::~UINode------\n");
}

}
}