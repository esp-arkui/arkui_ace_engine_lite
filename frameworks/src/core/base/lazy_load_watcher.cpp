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

#include "lazy_load_watcher.h"
#include "descriptor_utils.h"
#include "js_app_context.h"

namespace OHOS {
namespace ACELite {
LazyLoadWatcher::LazyLoadWatcher(Component *parent, Component *component, jerry_value_t descriptor)
    : parentComponent_(parent), currentComponent_(component), descriptor_(jerry_acquire_value(descriptor))
{
    isDescriptor_ = true;
    if (DescriptorUtils::IsIfDescriptor(descriptor)) {
        ifDescriptorValue_ = DescriptorUtils::IsIfDescriptorShown(descriptor);
    }
    JsAppContext::GetInstance()->RefLazyWatcherCount();
}

LazyLoadWatcher::LazyLoadWatcher(Component *component,
                                 jerry_value_t attrName,
                                 jerry_value_t getter,
                                 uint16_t keyId,
                                 bool isDescriptor)
    : currentComponent_(component),
      attrName_(jerry_acquire_value(attrName)),
      getter_(jerry_acquire_value(getter)),
      keyId_(keyId),
      isDescriptor_(isDescriptor)
{
    JsAppContext::GetInstance()->RefLazyWatcherCount();
}

LazyLoadWatcher::~LazyLoadWatcher()
{
    if (!IS_UNDEFINED(attrName_)) {
        jerry_release_value(attrName_);
    }
    if (!IS_UNDEFINED(getter_)) {
        jerry_release_value(getter_);
    }
    if (!IS_UNDEFINED(descriptor_)) {
        jerry_release_value(descriptor_);
    }
    JsAppContext::GetInstance()->DefLazyWatcherCount();
}
} // namespace ACELite
} // namespace OHOS
