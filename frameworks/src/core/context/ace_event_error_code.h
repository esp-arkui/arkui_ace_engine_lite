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

#ifndef OHOS_ACELITE_ACE_EVENT_ERROR_CODE_H
#define OHOS_ACELITE_ACE_EVENT_ERROR_CODE_H

#include "acelite_config.h"

#if defined(FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT)
#include "ace_event_id.h"
#include "memory_heap.h"
#include "non_copyable.h"
#include <cstdint>

namespace OHOS {
namespace ACELite {
class EventErrorCodePrint final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(EventErrorCodePrint);

    EventErrorCodePrint() = default;

    ~EventErrorCodePrint() = default;

    void AceEventPrint(uint8_t info2, uint8_t info3);

    void AceEventPrint(uint8_t info1, uint8_t info2, uint8_t info3);

    void AceErrorCodePrint(uint8_t info2, uint16_t rfu);
};
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT
#endif // OHOS_ACELITE_ACE_EVENT_ERROR_CODE_H