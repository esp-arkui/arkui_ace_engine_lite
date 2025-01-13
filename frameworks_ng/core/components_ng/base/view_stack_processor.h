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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_BASE_VIEW_STACK_PROCESSOR_H

#include <stack>
#include <iostream>
#include <memory>

#include "frame_node.h"
#include "../../pipline/element_register.h"

namespace OHOS{
namespace ACELite {
using namespace std;
enum ContainerType {
    STAGE_CONTAINER = 1,
    FA_CONTAINER,
    PA_SERVICE_CONTAINER,
    PA_DATA_CONTAINER,
    PA_FORM_CONTAINER,
    FA_SUBWINDOW_CONTAINER,
    COMPONENT_SUBWINDOW_CONTAINER = 10,
    PLUGIN_SUBCONTAINER = 20,
};

constexpr int32_t INSTANCE_ID_UNDEFINED = -1;
constexpr int32_t INSTANCE_ID_PLATFORM = -2;
constexpr int32_t CONTAINER_ID_DIVIDE_SIZE = 100000;
constexpr int32_t MIN_PLUGIN_SUBCONTAINER_ID = PLUGIN_SUBCONTAINER * CONTAINER_ID_DIVIDE_SIZE;
constexpr int32_t MIN_SUBCONTAINER_ID = COMPONENT_SUBWINDOW_CONTAINER * CONTAINER_ID_DIVIDE_SIZE;
constexpr int32_t MIN_PA_SERVICE_ID = PA_SERVICE_CONTAINER * CONTAINER_ID_DIVIDE_SIZE;
class ViewStackProcessor final {
public:
    static ViewStackProcessor* GetInstance();

    void Push(const shared_ptr<UINode>& element, bool isCustomView = false);

    void Pop();

    const std::shared_ptr<UINode>& GetMainElementNode() const;

    void PopContainer();

    bool IsEmpty() const
    {
        return elementsStack_.empty();
    }

    std::shared_ptr<UINode> Finish();

    void SetRecycleNodeId(int32_t recycleNodeId)
    {
        recycleNodeId_ = recycleNodeId;
    }

    int32_t GetRecycleNodeId()
    {
        const auto result = recycleNodeId_;
        recycleNodeId_ = ElementRegister::UndefinedElementId;
        return result;
    }

    void ClearStack()
    {
        auto emptyStack = std::stack<shared_ptr<UINode>>();
        elementsStack_.swap(emptyStack);
    }

    /**
     * get the elmtId to which all get access should be accounted
     * ElementRegister::UndefinedElementId; means no get access recording enabled
     */
    ElementIdType GetNodeIdToAccountFor() const
    {
        return accountGetAccessToNodeId_;
    }
    void SetNodeIdToAccountFor(ElementIdType elmtId)
    {
        accountGetAccessToNodeId_ = elmtId;
    }

    void StartGetAccessRecordingFor(int32_t elmtId)
    {
        accountGetAccessToNodeId_ = elmtId;
        reservedNodeId_ = elmtId;
        // if (containerId_ != OHOS::Ace::INSTANCE_ID_UNDEFINED) {
        //     restoreInstanceId_ = Container::CurrentId();
        //     ContainerScope::UpdateCurrent(containerId_);
        // }
    }

    void StopGetAccessRecording()
    {
        if (restoreInstanceId_ != INSTANCE_ID_UNDEFINED) {
            //ContainerScope::UpdateCurrent(restoreInstanceId_);
            restoreInstanceId_ = INSTANCE_ID_UNDEFINED;
        }
        accountGetAccessToNodeId_ = ElementRegister::UndefinedElementId;
        reservedNodeId_ = ElementRegister::UndefinedElementId;
    }

    void ImplicitPopBeforeContinue();

    FrameNode* GetMainFrameNode() const;
    bool ShouldPopImmediately();
private:
    static thread_local std::unique_ptr<ViewStackProcessor> instance;
    std::stack<shared_ptr<UINode>> elementsStack_;

    int32_t restoreInstanceId_ = INSTANCE_ID_UNDEFINED;

    ElementIdType recycleNodeId_ = ElementRegister::UndefinedElementId;
    // elmtId reserved for next component creation
    ElementIdType reservedNodeId_ = ElementRegister::UndefinedElementId;

    // elmtId to account get access to
    ElementIdType accountGetAccessToNodeId_ = ElementRegister::UndefinedElementId;

};
}
}
#endif
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                