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

#include "ace_lite_environment.h"
namespace OHOS {
namespace ACELite {
AceLiteEnvironment::AceLiteEnvironment() : id_(0), next(nullptr)
{
}

AceLiteEnvironment::~AceLiteEnvironment()
{
}

#ifdef FEATURE_TIMER_MODULE
TimerList* AceLiteEnvironment::GetTimerList()
{
    if (timerList_ == nullptr) {
        timerList_ = new TimerList();
        if (timerList_ == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "malloc timer heap memory failed.");
        }
    }
    return timerList_;
}

void AceLiteEnvironment::ClearTimerList()
{
    if (timerList_ != nullptr) {
        timerList_->ClearTimerList();
        delete (timerList_);
        timerList_ = nullptr;
    }
}
#endif

} // namespace ACELite
} // namespace OHOS
