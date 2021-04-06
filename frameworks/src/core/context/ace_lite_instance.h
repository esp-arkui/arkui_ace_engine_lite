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

#ifndef OHOS_ACELITE_INSTANCE_H
#define OHOS_ACELITE_INSTANCE_H
#include "acelite_config.h"

#include "ace_lite_environment.h"
#include "js_debugger_config.h"

namespace OHOS {
namespace ACELite {
#if ENABLED(JS_PROFILER)
#define START_TRACING(traceTag) AceLiteInstance::GetCurrentJSProfiler()->PushTrace(traceTag, 0, 0)
#define START_TRACING_WITH_COMPONENT_NAME(traceTag, componentNameId) \
    AceLiteInstance::GetCurrentJSProfiler()->PushTrace(traceTag, componentNameId, 0)
#define START_TRACING_WITH_EXTRA_INFO(traceTag, componentNameId, extraInfoId) \
    AceLiteInstance::GetCurrentJSProfiler()->PushTrace(traceTag, componentNameId, extraInfoId)
#define STOP_TRACING() AceLiteInstance::GetCurrentJSProfiler()->PopTrace()
#define OUTPUT_TRACE() AceLiteInstance::GetCurrentJSProfiler()->Output()
#else
#define START_TRACING(traceTag)
#define START_TRACING_WITH_COMPONENT_NAME(traceTag, componentNameId)
#define START_TRACING_WITH_EXTRA_INFO(traceTag, componentNameId, extraInfoId)
#define STOP_TRACING()
#define OUTPUT_TRACE()
#endif // ENABLED(JS_PROFILER)

#ifdef FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT
#define ACE_EVENT_PRINT(info2, info3) \
    AceLiteInstance::GetCurrentEventErrorCodePrint()->AceEventPrint(info2, info3)
#define ACE_FEATURE_EVENT_PRINT(info1, info2, info3) \
    AceLiteInstance::GetCurrentEventErrorCodePrint()->AceEventPrint(info1, info2, info3)
#define ACE_ERROR_CODE_PRINT(info2, rfu) \
    AceLiteInstance::GetCurrentEventErrorCodePrint()->AceErrorCodePrint(info2, rfu)
#else
#define ACE_EVENT_PRINT(info2, info3)
#define ACE_FEATURE_EVENT_PRINT(info1, info2, info3)
#define ACE_ERROR_CODE_PRINT(info2, rfu)
#endif // ENABLED(FEATURE_ACELITE_MC_EVENT_ERROR_CODE_PRINT)

#ifdef SIMULATOR_MEMORY_ANALYSIS
#define CLEAR_UP() AceLiteInstance::GetCurrentMemProc()->ClearUp()
#define SYS_MEMORY_TRACING() AceLiteInstance::GetCurrentMemProc()->SysMemTracing()
#define JERRY_MEMORY_TRACING() AceLiteInstance::GetCurrentMemProc()->JerryMemTracing()
#else
#define CLEAR_UP()
#define SYS_MEMORY_TRACING()
#define JERRY_MEMORY_TRACING()
#endif // ENABLED(SIMULATOR_MEMORY_ANALYSIS)

/**
 * @brief Global ACELITE Enviroment.
 */
class AceLiteInstance final : public MemoryHeap {
public:
    static AceLiteInstance *GetInstance();

    void CreateAceLiteEnvironment(uint8_t id);

    void CreateAceLiteEnvironment(uint8_t id, const char* name);

    void DeleteAceLiteEnvironment(uint8_t id);

    void ClearCurrentEnviroment() {
        currentEnvironment_ = nullptr;
    }

    AceLiteEnvironment* GetAceLiteEnvironmentList() {
        return environmentList_;
    }

    static CacheManager* GetCurrentCacheManager()
    {
        return GetInstance()->GetCurrentEnviroment()->GetCacheManager();
    }

    static JsAppContext& GetCurrentJsAppContext()
    {
        return GetInstance()->GetCurrentEnviroment()->GetJsAppContext();
    }

    static JsAppEnvironment& GetCurrentJsAppEnvironment()
    {

        return GetInstance()->GetCurrentEnviroment()->GetJsAppEnvironment();
    }

    static AsyncTaskManager* GetCurrentAsyncTaskManager()
    {
        return GetInstance()->GetCurrentEnviroment()->GetAsyncTaskManager();
    }

    static Debugger* GetCurrentDebugger()
    {
        return GetInstance()->GetCurrentEnviroment()->GetDebugger();
    }

    static DftImpl* GetCurrentDftImpl()
    {
        return GetInstance()->GetCurrentEnviroment()->GetDftImpl();
    }

    static FatalHandler* GetCurrentFatalHandler()
    {
        return GetInstance()->GetCurrentEnviroment()->GetFatalHandler();
    }

    static JerryElement* GetCurrentJerryElement()
    {
        return GetInstance()->GetCurrentEnviroment()->GetJerryElement();
    }

    static JSStateMachine* GetCurrentJSStateMachine()
    {
        return GetInstance()->GetCurrentEnviroment()->GetJSStateMachine();
    }

    static JSProfiler* GetCurrentJSProfiler()
    {
        return GetInstance()->GetCurrentEnviroment()->GetJSProfiler();
    }

    static EventErrorCodePrint* GetCurrentEventErrorCodePrint()
    {
        return GetInstance()->GetCurrentEnviroment()->GetEventErrorCodePrint();
    }

#ifdef SIMULATOR_MEMORY_ANALYSIS
    static AceMemProc* GetCurrentMemProc()
    {
        return GetInstance()->GetCurrentEnviroment()->GetMemProc();
    }
#endif

#ifdef FEATURE_TIMER_MODULE
    static TimerList* GetCurrentTimerList()
    {
        return GetInstance()->GetCurrentEnviroment()->GetTimerList();
    }
#endif

    AceLiteEnvironment* GetCurrentEnviroment();

    AceLiteEnvironment* GetAceLiteEnvironment(uint8_t id);
private:
    AceLiteInstance();

    ~AceLiteInstance();

    AceLiteEnvironment *environmentList_;

    AceLiteEnvironment *currentEnvironment_;
};
} // namespace ACELite
} // namespace OHOS

#endif // OHOS_ACELITE_INSTANCE_H
