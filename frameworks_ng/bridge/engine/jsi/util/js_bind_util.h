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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_ENGINE_JSI_UTIL_JS_BIND_UTIL_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_ENGINE_JSI_UTIL_JS_BIND_UTIL_H
#include "handler.h"
#include <iostream>
namespace OHOS{
namespace ACELite {
using namespace std;
class JSBindUtil {
public:
    static jerry_value_t Declare(const string& className);

    static void StaticMethod(const jerry_value_t& classObj, const string& funcName, jerry_external_handler_t handler);

private:


};
}
}


#endif