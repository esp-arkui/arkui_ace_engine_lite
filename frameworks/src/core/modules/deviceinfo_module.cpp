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
#include "acelite_config.h"
#ifdef FEATURE_MODULE_DEVICE_ENABLE
#include "deviceinfo_module.h"
#include "global.h"
#include "js_async_work.h"
#include "parameter.h"
#include "screen.h"

namespace OHOS {
namespace ACELite {
namespace {
JSIValue ExecuteAsyncWork(const JSIValue thisVal, const JSIValue* args,
    uint8_t argsNum, AsyncWorkHandler ExecuteFunc, bool flag = false)
{
    JSIValue undefValue = JSI::CreateUndefined();
    if (JSI::ValueIsUndefined(args[0])) {
        return undefValue;
    }
    FuncParams* params = new FuncParams();
    if (params == nullptr) {
        return undefValue;
    }
    params->thisVal = JSI::AcquireValue(thisVal);
    params->args = JSI::AcquireValue(args[0]);
    params->flag = flag;
    if (!(JsAsyncWork::DispatchAsyncWork(ExecuteFunc, reinterpret_cast<void *>(params)))) {
        JSI::ReleaseValueList(params->thisVal, params->args, ARGS_END);
        delete params;
        params = nullptr;
    }
    return undefValue;
}

void ExecuteGetInfo(void* data)
{
    FuncParams* params = reinterpret_cast<FuncParams *>(data);
    if (params == nullptr) {
        return;
    }
    JSIValue args = params->args;
    JSIValue thisVal = params->thisVal;
    JSIValue result = JSI::CreateObject();
    if (!DeviceInfoModule::GetProductInfo(result)) {
        JSIValue fail = JSI::GetNamedProperty(args, CB_FAIL);
        if (!JSI::ValueIsUndefined(fail)) {
            JSIValue errInfo = JSI::CreateString("System error");
            int error_code = 200;
            JSIValue errCode = JSI::CreateNumber(error_code);
            JSIValue argv[ARGC_TWO] = {errInfo, errCode};
            JSI::CallFunction(fail, thisVal, argv, ARGC_TWO);
            JSI::ReleaseValueList(fail, errInfo, errCode, ARGS_END);
        }
    } else {
        JSIValue success = JSI::GetNamedProperty(args, CB_SUCCESS);
        if (!JSI::ValueIsUndefined(success)) {
            JSI::CallFunction(success, thisVal, &result, ARGC_ONE);
            JSI::ReleaseValue(success);
        }
    }
    JSIValue complete = JSI::GetNamedProperty(args, CB_COMPLETE);
    if (!JSI::ValueIsUndefined(complete)) {
        JSI::CallFunction(complete, thisVal, nullptr, 0);
    }
    JSI::ReleaseValueList(complete, args, thisVal, result, ARGS_END);
    delete params;
    params = nullptr;
}
}

void InitDeviceModule(JSIValue exports)
{
    JSI::SetModuleAPI(exports, "getInfo", DeviceInfoModule::GetDeviceInfo);
}

bool DeviceInfoModule::GetAPILevel(JSIValue result)
{
    int apiLevel = GetSdkApiVersion();
    if (apiLevel < 1) {
        return false;
    }
    JSI::SetNumberProperty(result, "apiVersion", (double)apiLevel);
    return true;
}

JSIValue DeviceInfoModule::GetDeviceInfo(const JSIValue thisVal, const JSIValue* args, uint8_t argsNum)
{
    return ExecuteAsyncWork(thisVal, args, argsNum, ExecuteGetInfo);
}

bool DeviceInfoModule::GetDevType(JSIValue result)
{
    const char* deviceType = GetDeviceType();
    if (deviceType == nullptr) {
        return false;
    }
    JSI::SetStringProperty(result, "deviceType", deviceType);
    return true;
}

bool DeviceInfoModule::GetLanguage(JSIValue result)
{
    // because of MAX_LANGUAGE_LENGTH is little,we use array instead of pointer
    char langStr[MAX_LANGUAGE_LENGTH + 1] = {0};
    if (GLOBAL_GetLanguage(langStr, MAX_LANGUAGE_LENGTH) != 0) {
        JSI::SetStringProperty(result, "language", "");
    } else {
        JSI::SetStringProperty(result, "language", langStr);
    }
    return true;
}

bool DeviceInfoModule::GetProductInfo(JSIValue result)
{
    bool isSuccess = true;
    const char* brand =  GetBrand();
    const char* manufacture = GetManufacture();
    const char* model = GetProductModel();
    if (brand == nullptr || manufacture == nullptr || model == nullptr) {
        isSuccess = false;
    } else {
        JSI::SetStringProperty(result, "brand", brand);
        JSI::SetStringProperty(result, "manufacturer", manufacture);
        JSI::SetStringProperty(result, "model", model);
        JSI::SetStringProperty(result, "product", model);
    }
    if (isSuccess) {
        if (!DeviceInfoModule::GetDevType(result) ||
            !DeviceInfoModule::GetLanguage(result) ||
            !DeviceInfoModule::GetAPILevel(result) ||
            !DeviceInfoModule::GetRegion(result)) {
            isSuccess = false;
        }
    }

    Screen &screen = Screen::GetInstance();
    JSI::SetNumberProperty(result, "windowWidth", (double)screen.GetWidth());
    JSI::SetNumberProperty(result, "windowHeight", (double)screen.GetHeight());
    // set default value
    const uint8_t defaultScreenDensity = 195;
    const char * const defaultScreenShape = "rect";
    JSI::SetNumberProperty(result, "screenDensity", (double)defaultScreenDensity);
    JSI::SetStringProperty(result, "screenShape", defaultScreenShape);
    return isSuccess;
}

bool DeviceInfoModule::GetRegion(JSIValue result)
{
    // because of MAX_REGION_LENGTH is little,we use array instead of pointer
    char region[MAX_REGION_LENGTH + 1] = {0};
    if (GLOBAL_GetRegion(region, MAX_REGION_LENGTH) != 0) {
        JSI::SetStringProperty(result, "region", "");
    } else {
        JSI::SetStringProperty(result, "region", region);
    }
    return true;
}
} // ACELite
} // OHOS
#endif // FEATURE_MODULE_DEVICE_ENABLE
