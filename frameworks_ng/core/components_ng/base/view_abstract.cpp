#include "view_abstract.h"
#include "view_stack_processor.h"

namespace OHOS{
namespace ACELite {
void ViewAbstract::SetWidth(const int16_t& width)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!frameNode) {
        return;
    }

    auto pattern = frameNode->GetPattern();
    if (!pattern) {
        return;
    }

    pattern->SetWidth(width);
}

void ViewAbstract::SetHeight(const int16_t& height)
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!frameNode) {
        return;
    }

    auto pattern = frameNode->GetPattern();
    if (!pattern) {
        return;
    }

    pattern->SetHeight(height);
}

bool ViewAbstract::ShowPage()
{
    auto frameNode = ViewStackProcessor::GetInstance()->GetMainFrameNode();
    if (!frameNode) {
        return false;
    }

    auto pattern = frameNode->GetPattern();
    if (!pattern) {
        return false;
    }

    pattern->ShowPage();
}
}
}