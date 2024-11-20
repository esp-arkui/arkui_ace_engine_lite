#include "jsi_engine_instance.h"
#include "jsi_declarative_engine.h"

namespace OHOS {
namespace ACELite {
void JsEngineInstance::CreateDeclarativeJsEngine()
{
    jsEngine_ =dynamic_pointer_cast<JsiDeclarativeEngine>(std::make_shared<JsiDeclarativeEngine>());
}

const std::shared_ptr <JsEngine>& JsEngineInstance::getJsEngine() const {
    return jsEngine_;
}

}
}
