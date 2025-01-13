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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_UI_NODE_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_UI_NODE_H

#include "memory_heap.h"
#include <iostream>
#include <memory>

namespace OHOS{
namespace ACELite {
constexpr int32_t DEFAULT_NODE_SLOT = -1;
class UINode : public MemoryHeap  {
public:
    UINode(const std::string& tag, int32_t nodeId, bool isRoot = false);
    virtual ~UINode();

    virtual bool IsAtomicNode() const {};

    void MountToParent(const std::shared_ptr<UINode>& parent, int32_t slot = DEFAULT_NODE_SLOT, bool silently = false,
        bool addDefaultTransition = false, bool addModalUiextension = false);

    int32_t GetId() const
    {
        return nodeId_;
    }

    const std::string& GetTag() const
    {
        return tag_;
    }

    void SetRemoveSilently(bool removeSilently)
    {
        removeSilently_ = removeSilently;
    }

private:
    std::string tag_ = "UINode";
    int32_t nodeId_ = 0;
    int64_t accessibilityId_ = -1;
    bool removeSilently_ = true;
    bool isRoot_ = false;

};

}
}

#endif
