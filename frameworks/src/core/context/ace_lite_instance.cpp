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

void AceLiteInstance::CreateAceLiteEnvironment(uint64_t taskId) {
    CreateAceLiteEnvironment(taskId, "");
}

void AceLiteInstance::CreateAceLiteEnvironment(uint64_t taskId, const char* name) {
    AutoLockGuard lockGuard(lock_);
    AceLiteEnvironment *environment = new AceLiteEnvironment();
    if (environment == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "");
        return;
    }

//    environment->SetId(id_++);
    environment->SetTaskId(taskId);
    environment->SetName(name);
    if (taskId == 1) {
        currentEnvironment_ = environment;
    }
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

void AceLiteInstance::DeleteAceLiteEnvironment(uint64_t taskId) {
    AutoLockGuard lockGuard(lock_);
    if (environmentList_ == nullptr) {
        return;
    }

    AceLiteEnvironment *current = environmentList_;
    if (current->taskId_ == taskId) {
        environmentList_ = current->next;
        delete current;
        return;
    }

    AceLiteEnvironment *prev = nullptr;
    while (current != nullptr) {
        if (current->taskId_ == taskId) {
            prev->next = current->next;
            delete current;
            return;
        }
        prev = current;
        current = current->next;
    }
}

void AceLiteInstance::ClearCurrentEnvironment() {
    delete currentEnvironment_;
    currentEnvironment_ = nullptr;
}

AceLiteEnvironment* AceLiteInstance::GetAceLiteEnvironmentList() {
    return environmentList_;
}

AceLiteEnvironment& AceLiteInstance::GetCurrentEnvironment() {
    return *currentEnvironment_;
}

AceLiteEnvironment* AceLiteInstance::GetAceLiteEnvironment(uint64_t taskId) {

    AutoLockGuard lockGuard(lock_);
    if (environmentList_ == nullptr) {
        return nullptr;
    }
    AceLiteEnvironment *current = environmentList_;
    while (current != nullptr) {
        if (current->taskId_ == taskId) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}
} // namespace ACELite
} // namespace OHOS
