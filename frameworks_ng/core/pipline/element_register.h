/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_PIPLINE_ELEMENT_REGISTER_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_PIPLINE_ELEMENT_REGISTER_H

#include "ui_node.h"
#include <unordered_map>
#include <memory>

namespace OHOS{
namespace ACELite {
class UINode;
using ElementIdType = int32_t;
using namespace std;
class ElementRegister {
public:
    static constexpr ElementIdType UndefinedElementId = static_cast<ElementIdType>(-1);

    ElementRegister() = default;

    ElementRegister(const ElementRegister&) = delete;
    ElementRegister& operator=(const ElementRegister&) = delete;

    static ElementRegister& GetInstance() {
        static ElementRegister instance;
        return instance;
    }
 
    shared_ptr<UINode> GetNodeById(ElementIdType elementId);

    bool AddUINode(const std::shared_ptr<UINode>& node);
private:
    bool AddReferenced(ElementIdType elmtId, const std::weak_ptr<UINode>& referenced);


    ElementIdType lastestElementId_ = 0;
    // Map for created elements
    std::unordered_map<ElementIdType, std::weak_ptr<UINode>> itemMap_;

};




}
}
#endif
