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

#ifndef OHOS_ACELITE_INSTANCE_H
#define OHOS_ACELITE_INSTANCE_H
#include "acelite_config.h"

#include "ace_lite_environment.h"
#include "ace_lock.h"
#include "js_debugger_config.h"

namespace OHOS {
namespace ACELite {


/**
 * @brief Global ACELITE Enviroment.
 */
class AceLiteInstance final : public MemoryHeap {
public:
    static AceLiteInstance *GetInstance();

    void CreateAceLiteEnvironment(uint64_t taskId);

    void CreateAceLiteEnvironment(uint64_t taskId, const char* name);

    void DeleteAceLiteEnvironment(uint64_t taskId);

    void ClearCurrentEnvironment();

    AceLiteEnvironment* GetAceLiteEnvironmentList();

    AceLiteEnvironment& GetCurrentEnvironment();

    AceLiteEnvironment* GetAceLiteEnvironment(uint64_t taskId);


private:
    AceLiteInstance();

    ~AceLiteInstance();

    AceLiteEnvironment *environmentList_;

    AceLiteEnvironment *currentEnvironment_;

    LockType lock_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_INSTANCE_H
