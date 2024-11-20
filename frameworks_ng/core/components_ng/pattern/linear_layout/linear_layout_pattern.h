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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_PATTERN_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_LINEAR_LAYOUT_LINEAR_LAYOUT_PATTERN_H
#include "pattern.h"
#include "flex_layout.h"
#include "flex_layout_pattern.h"
namespace OHOS{
namespace ACELite {
class LinearLayoutPattern : public FlexLayoutPattern {
public:
    explicit LinearLayoutPattern(bool isVertical);
    ~LinearLayoutPattern() = default;
    void OnShow(UIView* view) const;

    void CreateNativeView();

    bool IsAtomicNode() const
    {
        return false;
    }

private:
    bool isVertical_ = false;
};
}
}

#endif
