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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_H

#include <iostream>
#include "gfx_utils/color.h"

namespace OHOS{
namespace ACELite {
class  ViewAbstractModel {
public:
    static ViewAbstractModel* GetInstance();
    virtual ~ViewAbstractModel() = default;

    // basic size
    virtual void SetWidth(const int16_t& width) = 0;
    virtual void SetHeight(const int16_t& height) = 0;
    virtual void SetBackgroundColor(const ColorType& color) = 0;

    virtual bool ShowPage() = 0;

    virtual void SetPadding(const int64_t& value) = 0;

    virtual void SetMargin(const int64_t& value) = 0;

};
}
}
#endif
