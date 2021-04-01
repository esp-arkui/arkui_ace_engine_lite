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

#include "ace_lite_instance.h"
namespace OHOS {
namespace ACELite {
AceLiteInstance *AceLiteInstance::GetInstance()
{
    static AceLiteInstance instance;
    return &instance;
}

AceLiteInstance::AceLiteInstance() : environmentList_(nullptr)
{
}

AceLiteInstance::~AceLiteInstance()
{
}

void AceLiteInstance::CreateAceLiteEnvironment(uint8_t id) {
    CreateAceLiteEnvironment(id, "");
}

void AceLiteInstance::CreateAceLiteEnvironment(uint8_t id, const char* name) {
    // 通过线程id绑定
    AceLiteEnvironment * environment = new AceLiteEnvironment();
    environment->SetId(id);
    environment->SetName(name);
    if (environmentList_ == nullptr) {
        environmentList_ = environment;
        return;
    }

    AceLiteEnvironment *current = environmentList_;
    AceLiteEnvironment *prev = nullptr;
    while (current != nullptr) {
        prev = current;
        current = current->next;
    }

    prev->next = environment;
}

void AceLiteInstance::DeleteAceLiteEnvironment(uint8_t id) {
    if (environmentList_ == nullptr) {
        return;
    }

    AceLiteEnvironment *current = environmentList_;
    if (current->id == id) {
        environmentList_ = current->next;
        delete current;
        return;
    }

    AceLiteEnvironment *prev = nullptr;
    while (current != nullptr) {
        if (current->id == id) {
            prev->next = current->next;
            return;
        }
        prev = current;
        current = current->next;
    }
    delete current;
}

AceLiteEnvironment* AceLiteInstance::GetCurrentEnviroment() {
    if (currentEnvironment_ == nullptr) {
        return GetAceLiteEnvironment(1);
    }
    return currentEnvironment_;
}

AceLiteEnvironment* AceLiteInstance::GetAceLiteEnvironment(uint8_t id) {
    if (environmentList_ == nullptr) {
        HILOG_INFO(HILOG_MODULE_ACE, "init...");
        CreateAceLiteEnvironment(id);
    }
    AceLiteEnvironment *current = environmentList_;
    while (current != nullptr) {
        if (current->id == id) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
} // namespace ACELite
} // namespace OHOS
