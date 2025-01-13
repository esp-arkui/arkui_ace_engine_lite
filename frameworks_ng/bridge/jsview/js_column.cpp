#include "js_column.h"

#include "../engine/jsi/jsi_engine_instance.h"
#include "../engine/jsi/jsi_declarative_engine.h"
#include "util/js_bind_util.h"
#include "../../core/components_ng/pattern/linear_layout/column_model.h"
#include "../../core/components_ng/pattern/linear_layout/column_model_ng.h"

namespace OHOS{
namespace ACELite {

ColumnModel* ColumnModel::GetInstance()
{
    static ColumnModelNG instance;
    return &instance;
}

void JSColumn::JSBind()
{
    printf("JSColum::JSBind()-------\n");

    jerry_value_t obj = JSBindUtil::Declare("Column");

    JSBindUtil::StaticMethod(obj, "create", create);

    JSBindUtil::StaticMethod(obj, "pop", JSViewAbstract::Pop);
    JSBindUtil::StaticMethod(obj, "height", JSViewAbstract::JsHeight);
    JSBindUtil::StaticMethod(obj, "width", JSViewAbstract::JsWidth);
    JSBindUtil::StaticMethod(obj, "size", JSViewAbstract::JsSize);

    JSBindUtil::StaticMethod(obj, "showPage", JSViewAbstract::JsShowPage);

}

jerry_value_t JSColumn::create(const jerry_value_t func,
                               const jerry_value_t context,
                               const jerry_value_t* args,
                               const jerry_length_t length)
{
    printf("JSColum::create()-------\n");
    
    ColumnModel::GetInstance()->Create();       //创建对象

    return jerry_create_boolean(true);
}

};
}
