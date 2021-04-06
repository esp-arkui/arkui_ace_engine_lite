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

#ifndef OHOS_ACELITE_ENVIRONMENT_H
#define OHOS_ACELITE_ENVIRONMENT_H
#include "acelite_config.h"
#include "async_task_manager.h"
#include "dft_impl.h"
#include "fatal_handler.h"
#include "js_app_context.h"
#include "js_app_environment.h"
#include "cache_manager.h"
#include "js_profiler.h"
#include "ace_event_error_code.h"
#include "presets/timer_module.h"
#include "mem_proc.h"

namespace OHOS {
namespace ACELite {
#ifdef CONSOLE_LOG_LINE_MAX_LENGTH
const int16_t LOG_BUFFER_SIZE = CONSOLE_LOG_LINE_MAX_LENGTH;
#else
const int16_t LOG_BUFFER_SIZE = 256; // use 256 as default if it's not config
#endif // CONSOLE_LOG_LINE_MAX_LENGTH

struct JerryElement final : public MemoryHeap {
    char logBuffer[LOG_BUFFER_SIZE] = {0};

    uint16_t logBufferIndex = 0;
};

struct JSStateMachine final : public MemoryHeap {
    int timerInitState = -1;
};

/**
 * @brief Global ACELITE Enviroment.
 */
class AceLiteEnvironment final : public MemoryHeap {
public:
    AceLiteEnvironment();

    ~AceLiteEnvironment();

    JsAppEnvironment& GetJsAppEnvironment()
    {
        return jsAppEnvironment_;
    }

    JsAppContext& GetJsAppContext()
    {
        return jsAppContext_;
    }

    AsyncTaskManager* GetAsyncTaskManager()
    {
        return &asyncTaskManager_;
    }

    FatalHandler* GetFatalHandler()
    {
        return &fatalHandler_;
    }

    DftImpl* GetDftImpl()
    {
        return &dftImpl_;
    }

    Debugger* GetDebugger()
    {
        return &debugger_;
    }

    JerryElement* GetJerryElement()
    {
        return &jerryElement_;
    }

    CacheManager* GetCacheManager()
    {
        return &cacheManager_;
    }

    JSProfiler* GetJSProfiler()
    {
        return &jsProfiler_;
    }

    EventErrorCodePrint* GetEventErrorCodePrint()
    {
        return &eventErrorCodePrint_;
    }

    JSStateMachine* GetJSStateMachine()
    {
        return &jsStateMachine_;
    }

    void SetName(const char* name) {
        this->name = name;
    }

    void SetId(uint8_t id) {
        this->id = id;
    }

#ifdef SIMULATOR_MEMORY_ANALYSIS
    AceMemProc* GetMemProc()
    {
        return &aceMemProc_;
    }
#endif

#ifdef FEATURE_TIMER_MODULE
    TimerList* GetTimerList();

    void ClearTimerList();
#endif

    uint8_t id;

    const char* name;

    AceLiteEnvironment *next;

private:
    JsAppContext jsAppContext_;

    JsAppEnvironment jsAppEnvironment_;

    AsyncTaskManager asyncTaskManager_;

    DftImpl dftImpl_;

    FatalHandler fatalHandler_;

    Debugger debugger_;

    JerryElement jerryElement_;

    CacheManager cacheManager_;

    JSProfiler jsProfiler_;

    EventErrorCodePrint eventErrorCodePrint_;

    JSStateMachine jsStateMachine_;

#ifdef SIMULATOR_MEMORY_ANALYSIS
    AceMemProc aceMemProc_;
#endif

#ifdef FEATURE_TIMER_MODULE
    TimerList *timerList_;
#endif
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_ENVIRONMENT_H
