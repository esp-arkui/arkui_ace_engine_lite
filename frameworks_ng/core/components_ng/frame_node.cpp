#include "frame_node.h"
#include "../pipline/element_register.h"
namespace OHOS{
namespace ACELite {

FrameNode::FrameNode(const std::string& tag, int32_t nodeId, const std::shared_ptr<Pattern>& pattern,
                    bool isRoot, bool isLayoutNode)
                    : UINode(tag, nodeId, isRoot), pattern_(pattern)
{

}

FrameNode::~FrameNode()
{

}



std::shared_ptr<FrameNode> FrameNode::GetOrCreateFrameNode(
    const std::string& tag, int32_t nodeId, const std::function<std::shared_ptr<Pattern>(void)>& patternCreator)
{
    auto frameNode = GetFrameNode(tag, nodeId);
    if (frameNode) {
        return frameNode;
    }

    auto pattern = patternCreator ? patternCreator() : make_shared<Pattern>();
    return CreateFrameNode(tag, nodeId, pattern);
}

shared_ptr<FrameNode> FrameNode::GetFrameNode(const std::string& tag, int32_t nodeId)
{
    auto frameNode = static_pointer_cast<FrameNode>(ElementRegister::GetInstance().GetNodeById(nodeId));
    if (frameNode == nullptr) {
        return nullptr;
    }
    if (frameNode->GetTag() != tag) {
        printf("FrameNode::GetFrameNode-------frameNode->GetTag() != tag\n");
    }


    return frameNode;
}

bool FrameNode::IsAtomicNode() const
{
    return pattern_->IsAtomicNode();
}

std::shared_ptr<FrameNode> FrameNode::CreateFrameNode (
        const std::string& tag, int32_t nodeId, const std::shared_ptr<Pattern>& pattern, bool isRoot)
{
    printf("CreateFrameNode-----------tag=[%s]\n", tag.c_str());
    auto frameNode = std::make_shared<FrameNode>(tag, nodeId, pattern, isRoot);
    ElementRegister::GetInstance().AddUINode(frameNode);

    frameNode->InitializePatternAndContext();
    return frameNode;
}


void FrameNode::InitializePatternAndContext()
{
    printf("FrameNode::InitializePatternAndContext----------\n");
}

void FrameNode::MarkModifyDone()
{

}

}
}
