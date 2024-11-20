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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_PATTERN_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_PATTERN_H

#include "../frame_node.h"
#include "ui_view.h"
#include "layout_property.h"
#include <memory>

namespace OHOS{
namespace ACELite {
class FrameNode;
class Pattern {
public:
    Pattern();
    virtual ~Pattern() = default;

    void AttachToFrameNode(const std::weak_ptr<FrameNode>& frameNode)
    {
        if (frameNode_.lock() && frameNode.lock() && frameNode_.lock() == frameNode.lock()) {
            return;
        }
        frameNode_ = frameNode;
        OnAttachToFrameNode();
    }

    std::shared_ptr<FrameNode> GetHost() const
    {
        return frameNode_.lock();
    }

    virtual void CreateNativeView()
    {
        nativeView_ = std::make_shared<UIView>();
    }

    std::shared_ptr<UIView> GetNativeView() {
        return nativeView_;
    }

    virtual std::shared_ptr<LayoutProperty> CreateLayoutProperty()
    {
        return std::make_shared<LayoutProperty>();
    }

    virtual bool IsAtomicNode() const
    {
        return true;
    }

    virtual void SetWidth(const int16_t &width);
    virtual void SetHeight(const int16_t &height);

    virtual bool ShowPage();

    virtual void SetBackgroundColor(const ColorType& color);
    virtual void SetPadding(const int64_t& value);

    virtual void SetMargin(const int64_t& value);


protected:
    virtual void OnAttachToFrameNode() {}
    std::weak_ptr<FrameNode> frameNode_;
    std::shared_ptr<UIView> nativeView_;
};
}
}


#endif
