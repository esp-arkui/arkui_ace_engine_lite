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

#ifndef OHOS_ACELITE_DEVICEINFO_MODULE_H
#define OHOS_ACELITE_DEVICEINFO_MODULE_H

#include "acelite_config.h"
#include "jsi.h"

namespace OHOS {
namespace ACELite {
struct FuncParams {
    JSIValue args = JSI::CreateUndefined();
    JSIValue thisVal = JSI::CreateUndefined();
    bool flag = false;
};   
class DeviceInfoModule {
public:
    DeviceInfoModule() = default;
    ~DeviceInfoModule() = default;

    static JSIValue GetDeviceInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum);
    static bool GetProductInfo(JSIValue result);

private:
    static bool GetLanguage(JSIValue result);
    static bool GetRegion(JSIValue result);
    static bool GetAPILevel(JSIValue result);
    static bool GetDevType(JSIValue result);
};
} // ACELite
} // OHOS
#endif // OHOS_ACELITE_DEVICEINFO_MODULE_H
