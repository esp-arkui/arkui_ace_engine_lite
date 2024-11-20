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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_ENGINE_JSI_JSI_ENGINE_INSTANCE_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_ENGINE_JSI_JSI_ENGINE_INSTANCE_H

#include <memory>
#include <iostream>
#include "../common/js_engine.h"

namespace OHOS {
namespace ACELite {
class JsEngineInstance {
public:
    JsEngineInstance() = default;
    virtual ~JsEngineInstance() = default;
    JsEngineInstance(const JsEngineInstance&) = delete;
    JsEngineInstance& operator=(const JsEngineInstance&) = delete;

    static JsEngineInstance& getInstance() {
        static JsEngineInstance instance;
        return instance;
    }

    void CreateDeclarativeJsEngine();
    const std::shared_ptr<JsEngine>& getJsEngine() const;

private:
    std::shared_ptr<JsEngine> jsEngine_;
};
}
}
#endif
