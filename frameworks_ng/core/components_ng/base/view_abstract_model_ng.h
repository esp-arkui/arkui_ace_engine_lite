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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_CORE_COMPONENTS_NG_BASE_VIEW_ABSTRACT_MODEL_NG_H

#include "view_abstract_model.h"
#include "view_abstract.h"
namespace OHOS{
namespace ACELite {
class  ViewAbstractModelNG : public ViewAbstractModel {
public:
    ~ViewAbstractModelNG() override = default;

    void SetWidth(const int16_t& width) override;
    void SetHeight(const int16_t& height) override;
    bool ShowPage() override;

    void SetBackgroundColor(const ColorType& color) override;
    void SetPadding(const int64_t& value) override;
    void SetMargin(const int64_t& value) override;

private:

};

}
}
#endif
