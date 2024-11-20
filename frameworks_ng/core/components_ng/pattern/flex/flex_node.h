/*
 * Copyright (c) 2021 Huawei Device Co., Ltd.
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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_FLEX_FLEX_NODE_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_FLEX_FLEX_NODE_H

#include "../../frame_node.h"


namespace OHOS{
namespace ACELite {
class FlexNode : public FrameNode {
    FlexNode(const std::string& tag, int32_t nodeId, const shared_ptr<Pattern>& pattern);
    ~FlexNode() override;

private:


};
}
}
#endif


 