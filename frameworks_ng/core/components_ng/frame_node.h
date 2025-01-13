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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_FRAME_NODE_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_FRAME_NODE_H
#include <functional>

#include "ui_node.h"
#include "pattern/pattern.h"
#include <memory>
#include "../pipline/render_context.h"

// FrameNode will display rendering region in the screen.
namespace OHOS{
namespace ACELite {
class Pattern;
using namespace std;
class FrameNode: public UINode {
public:
    FrameNode(const std::string& tag, int32_t nodeId, const std::shared_ptr<Pattern>& pattern,
        bool isRoot = false, bool isLayoutNode = false);

    ~FrameNode() override;

    bool IsAtomicNode() const override;

    void MarkBuildDone();
    
    virtual void MarkModifyDone();

    static shared_ptr<FrameNode> GetFrameNode(const std::string& tag, int32_t nodeId);

    static std::shared_ptr<FrameNode> GetOrCreateFrameNode(
        const std::string& tag, int32_t nodeId, const std::function<std::shared_ptr<Pattern>(void)>& patternCreator);


    static std::shared_ptr<FrameNode> CreateFrameNode(
        const std::string& tag, int32_t nodeId, const std::shared_ptr<Pattern>& pattern, bool isRoot = false);

    void InitializePatternAndContext();

    // const std::shared_ptr<RenderContext>& GetRenderContext() const
    // {
    //     return renderContext_;
    // }

    std::shared_ptr<Pattern> GetPattern() {
        return pattern_;
    }


private:
    std::shared_ptr<Pattern> pattern_;

};


}
}

#endif
