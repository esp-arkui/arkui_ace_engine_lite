#include "text_model_ng.h"
#include "text_pattern.h"
#include "view_stack_processor.h"


namespace OHOS{
namespace ACELite {
void TextModelNG::Create(const std::string& content)
{
    printf("TextModelNG::Create()-------\n");
    auto* stack = ViewStackProcessor::GetInstance();
    auto frameNode = FrameNode::GetOrCreateFrameNode("Text", 2,
        static_cast<std::function<std::shared_ptr<TextPattern>()>>(createTextPattern));
    if (!frameNode) {
        return;
    }

    stack->Push(frameNode);
    auto pattern = static_pointer_cast<TextPattern>(frameNode->GetPattern());
    if (!pattern) {
        return;
    }

    pattern->SetText(content);
    currentPattern_  = pattern;

    //pattern->ShowPage();
}
}
}
