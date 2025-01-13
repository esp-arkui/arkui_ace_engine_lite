#include "element_register.h"


namespace OHOS{
namespace ACELite {

bool ElementRegister::AddUINode(const std::shared_ptr<UINode>& node)
{
    if (!node || (node->GetId() == ElementRegister::UndefinedElementId)) {
        return false;
    }

    return AddReferenced(node->GetId(), node);
}

bool ElementRegister::AddReferenced(ElementIdType elmtId, const std::weak_ptr<UINode>& referenced)
{
    auto result = itemMap_.emplace(elmtId, referenced);
    if (!result.second) {
        printf("AddReferenced----error\n");
    }

    lastestElementId_ = elmtId;
    return result.second;
}

shared_ptr<UINode> ElementRegister::GetNodeById(ElementIdType elementId)
{
    if (elementId == ElementRegister::UndefinedElementId) {
        return nullptr;
    }

    auto position = itemMap_.find(elementId);
    return position == itemMap_.end() ? nullptr : position->second.lock();

}

}
}