#include "js_bind_util.h"

namespace OHOS{
namespace ACELite {

jerry_value_t JSBindUtil::Declare(const string& className)
{
    jerry_value_t globalObject = jerry_get_global_object();
    jerry_value_t classObj;
    if (!className.empty()) {
        classObj = jerry_create_object();
        jerry_release_value(jerryx_set_property_str(globalObject, className.c_str(), classObj));
        jerry_release_value(globalObject);
    } else {
        classObj = globalObject;
    }

    return classObj;
}

void JSBindUtil::StaticMethod(const jerry_value_t& classObj, const string& funcName, jerry_external_handler_t handler)
{
    if (funcName.empty() || handler == nullptr || jerry_value_is_undefined(classObj)) {
        printf("JSBindUtil::StaticMethod---has return------");
        return;
    }

    jerry_value_t func = jerry_create_external_function(handler);
    jerryx_set_property_str(classObj, funcName.c_str(), func);
    jerry_release_value(func);
}
}
}