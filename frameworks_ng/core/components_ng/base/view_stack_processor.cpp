#include "view_stack_processor.h"

namespace OHOS{
namespace ACELite {
const shared_ptr<UINode> INVALID_NODE = nullptr;
thread_local std::unique_ptr<ViewStackProcessor> ViewStackProcessor::instance = nullptr;

ViewStackProcessor* ViewStackProcessor::GetInstance()
{
    if (!instance) {
        instance.reset(new ViewStackProcessor);
    }
    return instance.get();
}

void ViewStackProcessor::Push(const shared_ptr<UINode>& element, bool isCustomView)
{
    if (ShouldPopImmediately()) {
        Pop();
    }
    element->SetRemoveSilently(false);
    elementsStack_.push(element);
}

void ViewStackProcessor::Pop()
{
    if (elementsStack_.empty() || elementsStack_.size() == 1) {
        return;
    }

    auto currentNode = Finish();
    auto parent = GetMainElementNode();
}

const std::shared_ptr<UINode>& ViewStackProcessor::GetMainElementNode() const
{   
    if (elementsStack_.empty()) {
        return INVALID_NODE;
    }
    return elementsStack_.top();
}

std::shared_ptr<UINode> ViewStackProcessor::Finish()
{
    if (elementsStack_.empty()) {
        return nullptr;
    }
    auto element = std::move(elementsStack_.top());
    elementsStack_.pop();
    auto frameNode = std::dynamic_pointer_cast<FrameNode>(element);
    if (frameNode) {
        //frameNode->MarkBuildDone();
        //frameNode->MarkModifyDone();
        //auto renderContext = frameNode->GetRenderContext();
        //if (renderContext) {
            //to do
            //renderContext->SetNeedDebugBoundary(true);
        //}
    }
    // ForEach Partial Update Path.
    // if (AceType::InstanceOf<ForEachNode>(element)) {
    //     auto forEachNode = AceType::DynamicCast<ForEachNode>(element);
    //     forEachNode->CompareAndUpdateChildren();
    // }



    return std::dynamic_pointer_cast<UINode>(frameNode);
}

FrameNode* ViewStackProcessor::GetMainFrameNode() const 
{
    auto uiNode = GetMainElementNode();
    if (!uiNode) {
        return nullptr;
    }

    return dynamic_cast<FrameNode*>(uiNode.get());
}

void ViewStackProcessor::ImplicitPopBeforeContinue()
{
    if ((elementsStack_.size() > 1) && ShouldPopImmediately()) {
        Pop();
    }
}

bool ViewStackProcessor::ShouldPopImmediately()
{
    if (elementsStack_.size() <= 1) {
        return false;
    }
    // for custom node and atomic node, just pop top node when next node is coming.
    return GetMainElementNode()->IsAtomicNode();
}

void ViewStackProcessor::PopContainer()
{
    auto top = GetMainElementNode();
    // for container node.
    if (top && !top->IsAtomicNode()) {
        Pop();
        return;
    }

    while (top && (top->IsAtomicNode())) {
        if (elementsStack_.size() == 1) {
            return;
        }
        Pop();
        top = GetMainElementNode();
    }
    Pop();
}
}
}
