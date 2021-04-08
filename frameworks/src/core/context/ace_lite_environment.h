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

#if ENABLED(JS_PROFILER)
#define START_TRACING(traceTag) AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetJSProfiler().PushTrace(traceTag, 0, 0)
#define START_TRACING_WITH_COMPONENT_NAME(traceTag, componentNameId) \
    AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetJSProfiler().PushTrace(traceTag, componentNameId, 0)
#define START_TRACING_WITH_EXTRA_INFO(traceTag, componentNameId, extraInfoId) \
    AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetJSProfiler().PushTrace(traceTag, componentNameId, extraInfoId)
#define STOP_TRACING() AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetJSProfiler().PopTrace()
#define OUTPUT_TRACE() AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetJSProfiler().Output()
#else
#define START_TRACING(traceTag)
#define START_TRACING_WITH_COMPONENT_NAME(traceTag, componentNameId)
#define START_TRACING_WITH_EXTRA_INFO(traceTag, componentNameId, extraInfoId)
#define STOP_TRACING()
#define OUTPUT_TRACE()
#endif // ENABLED(JS_PROFILER)

#ifdef FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT
#define ACE_EVENT_PRINT(info2, info3) \
    AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetEventErrorCodePrint().AceEventPrint(info2, info3)
#define ACE_FEATURE_EVENT_PRINT(info1, info2, info3) \
    AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetEventErrorCodePrint().AceEventPrint(info1, info2, info3)
#define ACE_ERROR_CODE_PRINT(info2, rfu) \
    AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetEventErrorCodePrint().AceErrorCodePrint(info2, rfu)
#else
#define ACE_EVENT_PRINT(info2, info3)
#define ACE_FEATURE_EVENT_PRINT(info1, info2, info3)
#define ACE_ERROR_CODE_PRINT(info2, rfu)
#endif // ENABLED(FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT)

#ifdef SIMULATOR_MEMORY_ANALYSIS
#define CLEAR_UP() AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetMemProc().ClearUp()
#define SYS_MEMORY_TRACING() AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetMemProc().SysMemTracing()
#define JERRY_MEMORY_TRACING() AceLiteInstance::GetInstance()->GetCurrentEnvironment().GetMemProc().JerryMemTracing()
#else
#define CLEAR_UP()
#define SYS_MEMORY_TRACING()
#define JERRY_MEMORY_TRACING()
#endif // ENABLED(SIMULATOR_MEMORY_ANALYSIS)

/**
 * @brief The RuntimeContext struct contains js application runtime fields
 */
struct RuntimeContext final : public MemoryHeap {
    char logBuffer[LOG_BUFFER_SIZE] = {0};

    uint16_t logBufferIndex = 0;

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

    AsyncTaskManager& GetAsyncTaskManager()
    {
        return asyncTaskManager_;
    }

    FatalHandler& GetFatalHandler()
    {
        return fatalHandler_;
    }

    DftImpl& GetDftImpl()
    {
        return dftImpl_;
    }

    Debugger& GetDebugger()
    {
        return debugger_;
    }

    CacheManager& GetCacheManager()
    {
        return cacheManager_;
    }

    JSProfiler& GetJSProfiler()
    {
        return jsProfiler_;
    }

    EventErrorCodePrint& GetEventErrorCodePrint()
    {
        return eventErrorCodePrint_;
    }

    RuntimeContext* GetRuntimeContext()
    {
        return &runtimeContext_;
    }

    void SetName(const char* name) {
        this->name_ = name;
    }

    void SetId(uint8_t id) {
        this->id_ = id;
    }

    void SetTaskId(uint64_t taskId) {
        this->taskId_ = taskId;
    }

#ifdef SIMULATOR_MEMORY_ANALYSIS
    AceMemProc& GetMemProc()
    {
        return aceMemProc_;
    }
#endif

#ifdef FEATURE_TIMER_MODULE
    TimerList* GetTimerList();

    void ClearTimerList();
#endif
    uint64_t taskId_;

    uint8_t id_;

    const char* name_;

    AceLiteEnvironment *next;

private:
    JsAppContext jsAppContext_;

    JsAppEnvironment jsAppEnvironment_;

    AsyncTaskManager asyncTaskManager_;

    DftImpl dftImpl_;

    FatalHandler fatalHandler_;

    Debugger debugger_;

    CacheManager cacheManager_;

    JSProfiler jsProfiler_;

    EventErrorCodePrint eventErrorCodePrint_;

    RuntimeContext runtimeContext_;

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
