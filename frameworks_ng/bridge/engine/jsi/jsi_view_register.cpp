#include "jsi_view_register.h"

#include "js_column.h"
#include "js_text.h"

namespace OHOS{
namespace ACELite {


void JsRegisterViews()
{
    printf("JsRegisterViews----------\n");

    JSColumn::JSBind();
    JSText::JSBind();

}


}
}
