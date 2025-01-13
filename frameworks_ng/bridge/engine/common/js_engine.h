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


#ifndef ARKUI_ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIGE_ENGINE_COMMON_JS_ENGINE_H
#define ARKUI_ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIGE_ENGINE_COMMON_JS_ENGINE_H
#include "memory_heap.h"
#include <iostream>


namespace OHOS {
namespace ACELite {
//虚函数，初例化对象中进行
class JsEngine : public MemoryHeap {

public:
    JsEngine() = default;
    virtual bool InitJsEnv() = 0;


};
}
}

#endif