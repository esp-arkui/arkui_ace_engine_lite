#include "flex_node.h"


namespace OHOS{
namespace ACELite {
FlexNode::FlexNode(const std::string& tag, int32_t nodeId, const shared_ptr<Pattern>& pattern)
            : FrameNode(tag, nodeId, pattern)
{
//    nativeView_.SetStyle(STYLE_BACKGROUND_OPA, 100);
//    Style style = StyleDefault::GetDefaultStyle();
//    style.lineColor_ = Color::Red();
//    circleProgress_->SetBackgroundStyle(style);
}

FlexNode::~FlexNode()
{

}
}
}
