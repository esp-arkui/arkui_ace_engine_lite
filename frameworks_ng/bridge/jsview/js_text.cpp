#include "js_text.h"
#include "util/js_bind_util.h"
#include "text_model_ng.h"


namespace OHOS {
namespace ACELite {

TextModel* TextModel::GetInstance()
{
    static TextModelNG instance;
    return &instance;
}

void JSText::JSBind()
{
    jerry_value_t obj = JSBindUtil::Declare("Text");

    JSBindUtil::StaticMethod(obj, "create", create);
    JSBindUtil::StaticMethod(obj, "pop", JSViewAbstract::Pop);
    JSBindUtil::StaticMethod(obj, "height", JSViewAbstract::JsHeight);
    JSBindUtil::StaticMethod(obj, "width", JSViewAbstract::JsWidth);

    JSBindUtil::StaticMethod(obj, "showPage", JSViewAbstract::JsShowPage);

}

jerry_value_t JSText::create(const jerry_value_t func,
                            const jerry_value_t context,
                            const jerry_value_t* args,
                            const jerry_length_t length)
{
    


    TextModel::GetInstance()->Create("hello");

    return jerry_create_boolean(true);
}

}
}




