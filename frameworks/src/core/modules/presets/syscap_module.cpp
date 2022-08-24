/*
 * Copyright (c) 2022-2022 Huawei Device Co., Ltd.
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
#if (FEATURE_SYSCAP_MODULE == 1)
#include <string.h>
#include "syscap_module.h"
#include "ace_mem_base.h"
#ifndef __LITEOS_M__
#include "systemcapability.h"
#endif  __LITEOS_M__

namespace OHOS {
namespace ACELite {
const uint16_t SYSCAP_BUFFER_SIZE = 128;
#ifdef __LITEOS_M__
enum ConfigStatus {
    ENABLE = 0,
    DISABLE,
};

typedef struct {
    char *name;
    enum ConfigStatus type;
} SysCapDef;

static const SysCapDef g_syscap[] = {
    {"SystemCapability.ArkUI.ArkUI.Lite", ENABLE},
    {"SystemCapability.BundleManager.PackingTool", ENABLE},
    {"SystemCapability.Communication.SoftBus.Core", ENABLE},
    {"SystemCapability.Communication.Bluetooth.Lite", ENABLE},
    {"SystemCapability.Communication.NFC.Core", ENABLE},
    {"SystemCapability.Location.Location.Lite", ENABLE},
    {"SystemCapability.PowerManager.PowerManager.Lite", ENABLE},
    {"SystemCapability.PowerManager.BatteryManager.Lite", ENABLE},
    {"SystemCapability.Customization.ConfigPolicy", ENABLE},
    {"SystemCapability.HiviewDFX.HiLogLite", ENABLE},
    {"SystemCapability.HiviewDFX.HiviewLite", ENABLE},
    {"SystemCapability.HiviewDFX.HiEventLite", ENABLE},
    {"SystemCapability.Update.UpdateService", ENABLE},
    {"SystemCapability.FileManagement.File.FileIO", ENABLE},
    {"SystemCapability.FileManagement.File.Environment", ENABLE},
    {"SystemCapability.Startup.SystemInfo", ENABLE}
};

static int GetSysCapNum()
{
    return sizeof(g_syscap) / sizeof(SysCapDef);
}

static bool HasSystemCapability(const char *cap)
{
    int sysCapNum = GetSysCapNum();
    for (int i = 0; i < sysCapNum; i++) {
        if (strcmp(cap, g_syscap[i].name) == 0) {
            if (g_syscap[i].type == ENABLE) {
                return true;
            } else {
                return false;
            }
        }
    }
    return false;
}
#endif // __LITEOS_M__

void SyscapModule::Init()
{
    const char * const canIUse = "canIUse";
    CreateNamedFunction(canIUse, CanIUse);
}

jerry_value_t SyscapModule::CheckSyscap(const jerry_value_t func,
                                        const jerry_value_t context,
                                        const jerry_value_t *args,
                                        const jerry_length_t argsNum,
                                        bool repeated)
{
    (void)func;     /* unused */
    (void)context;  /* unused */
    (void)repeated; /* unused */

    const uint8_t leastArguments = 1;
    if ((argsNum != leastArguments)) {
        return UNDEFINED;
    }

    jerry_value_t strVal;
    if (jerry_value_is_symbol(args[0])) {
        strVal = jerry_get_symbol_descriptive_string(args[0]);
    } else {
        strVal = jerry_value_to_string(args[0]);
    }

    if (jerry_value_is_error(strVal)) {
        jerry_release_value(strVal);
        return jerry_create_boolean(false);
    }

    jerry_length_t length = jerry_get_utf8_string_length(strVal);
    if (length >= SYSCAP_BUFFER_SIZE) {
        jerry_release_value(strVal);
        return jerry_create_boolean(false);
    }

    jerry_char_t buffer[SYSCAP_BUFFER_SIZE] = {0};
    jerry_size_t syscapStrSize = jerry_string_to_utf8_char_buffer(strVal, buffer, length);
    if (syscapStrSize == 0) {
        jerry_release_value(strVal);
        return jerry_create_boolean(false);
    }
    const char *syscapString = (char *)buffer;
    bool ret = HasSystemCapability(syscapString);

    jerry_release_value(strVal);
    return jerry_create_boolean(ret);
}
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_SYSCAP_MODULE
