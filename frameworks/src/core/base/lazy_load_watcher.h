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

#ifndef OHOS_ACELITE_LAZY_LOAD_WATCHER_H
#define OHOS_ACELITE_LAZY_LOAD_WATCHER_H

#include "component.h"
#include "jerryscript-core.h"
#include "js_fwk_common.h"
#include "non_copyable.h"

namespace OHOS {
namespace ACELite {
class LazyLoadWatcher final : public MemoryHeap {
public:
    ACE_DISALLOW_COPY_AND_MOVE(LazyLoadWatcher);

    LazyLoadWatcher(Component *parent,
                    Component *component,
                    jerry_value_t descriptor);

    LazyLoadWatcher(Component *component,
                    jerry_value_t attrName,
                    jerry_value_t getter,
                    uint16_t keyId,
                    bool isDescriptor = false);

    ~LazyLoadWatcher();

    jerry_value_t GetAttrName() const
    {
        return attrName_;
    }

    jerry_value_t GetAttrGetter() const
    {
        return getter_;
    }

    uint16_t GetKeyId() const
    {
        return keyId_;
    }

    bool IsDescriptor() const
    {
        return isDescriptor_;
    }

    jerry_value_t GetDescriptor() const
    {
        return descriptor_;
    }

    Component *GetCurrentComponent() const
    {
        return currentComponent_;
    }

    Component *GetParentComponent() const
    {
        return parentComponent_;
    }

    bool GetDescriptorIfValue() const
    {
        return ifDescriptorValue_;
    }

private:
    Component *parentComponent_ = nullptr;
    Component *currentComponent_ = nullptr;
    jerry_value_t attrName_ = UNDEFINED;
    jerry_value_t getter_ = UNDEFINED;
    jerry_value_t descriptor_ = UNDEFINED;
    uint16_t keyId_ = K_UNKNOWN;
    bool isDescriptor_ = false;
    bool ifDescriptorValue_ = false;
};
} // namespace ACELite
} // namespace OHOS
#endif // OHOS_ACELITE_LAZY_LOAD_WATCHER_H
