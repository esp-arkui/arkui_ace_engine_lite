#include "js_view_abstract.h"
#include "view_abstract_model.h"
#include "view_abstract_model_ng.h"
#include "view_stack_processor.h"
#include <limits>
namespace OHOS{
namespace ACELite {
using namespace std;
ViewAbstractModel* ViewAbstractModel::GetInstance()
{
    static ViewAbstractModelNG instance;
    return &instance;
}

void JSViewAbstract::JSBind()
{
    printf("JSViewAbstract::JSBind()-------\n");
}

jerry_value_t JSViewAbstract::JsShowPage(const jerry_value_t func,
                         const jerry_value_t context,
                         const jerry_value_t* args,
                         const jerry_length_t length)
{
    if (JsShowPage()) {
        return jerry_create_boolean(true);
    }

    return jerry_create_boolean(false);

}

jerry_value_t JSViewAbstract::Pop(const jerry_value_t func,
                            const jerry_value_t context,
                            const jerry_value_t* args,
                            const jerry_length_t length)
{
    ViewStackProcessor::GetInstance()->Pop();
    return jerry_create_boolean(true);
}

jerry_value_t JSViewAbstract::JsBackgroundColor(const jerry_value_t func,
                                                const jerry_value_t context,
                                                const jerry_value_t* args,
                                                const jerry_length_t length)
{
    if (length < 1 || !jerry_value_is_string(args[0])) {
        jerry_create_boolean(false);
    }
 
    jerry_size_t size = jerry_get_string_size(args[0]);
    jerry_char_t *buffer = static_cast<jerry_char_t *>(ace_malloc(sizeof(jerry_char_t) * (size + 1)));
    jerry_size_t buffLength = jerry_string_to_char_buffer(args[0], buffer, size);
    if ((buffLength == 0) || (buffLength > size)) {
        ace_free(buffer);
        buffer = nullptr;
        return jerry_create_boolean(false);
    }
    buffer[buffLength] = '\0';

    ColorType color = JSViewAbstract::parseColor(buffer, size);

    ViewAbstractModel::GetInstance()->SetBackgroundColor(color);

}

jerry_value_t JSViewAbstract::JsPadding(const jerry_value_t func,
                                        const jerry_value_t context,
                                        const jerry_value_t* args,
                                        const jerry_length_t length)
{
    if (length < 1 || !jerry_value_is_number(args[0])) {
        jerry_create_boolean(false);
    }

    double value = jerry_get_number_value(args[0]);

    ViewAbstractModel::GetInstance()->SetPadding(static_cast<int64_t>(value));
}

ColorType JSViewAbstract::parseColor(const jerry_char_t* colorStr, jerry_size_t colorStrLen) {
    ColorType color = {0, 0, 0}; // 默认颜色为黑色

    if (colorStrLen == 7 && colorStr[0] == '#') {
        color.red = static_cast<uint8_t>(std::strtol(reinterpret_cast<const char*>(colorStr + 1), nullptr, 16));
        color.green = static_cast<uint8_t>(std::strtol(reinterpret_cast<const char*>(colorStr + 3), nullptr, 16));
        color.blue = static_cast<uint8_t>(std::strtol(reinterpret_cast<const char*>(colorStr + 5), nullptr, 16));
    } else {

    }

    return color;
}

jerry_value_t JSViewAbstract::JsMargin(const jerry_value_t func,
            const jerry_value_t context,
            const jerry_value_t* args,
            const jerry_length_t length)
{
    if (length < 1 || !jerry_value_is_number(args[0])) {
        jerry_create_boolean(false);
    }

    double value = jerry_get_number_value(args[0]);

    ViewAbstractModel::GetInstance()->SetMargin(static_cast<int64_t>(value));
}

jerry_value_t JSViewAbstract::JsLayoutWeight(const jerry_value_t func,
            const jerry_value_t context,
            const jerry_value_t* args,
            const jerry_length_t length)
{
    //没找到对应方法
}

static jerry_value_t JsconstraintSize(const jerry_value_t func,
            const jerry_value_t context,
            const jerry_value_t* args,
            const jerry_length_t length)
{
    //没找到对应方法
}


jerry_value_t JSViewAbstract::JsHeight(const jerry_value_t func,
                        const jerry_value_t context,
                        const jerry_value_t* args,
                        const jerry_length_t length)
{
    printf("JSFlex::JsHeight-------\n");
    if (length < 1 || !jerry_value_is_number(args[0])) {
        return jerry_create_boolean(false);
    }

    double number = jerry_get_number_value(args[0]);

    if (number < static_cast<double>(std::numeric_limits<int16_t>::min()) ||
        number > static_cast<double>(std::numeric_limits<int16_t>::max())) {
        return jerry_create_boolean(false);
    }

    JsHeight(static_cast<int16_t>(number));

    return jerry_create_boolean(true);
}

jerry_value_t JSViewAbstract::JsWidth(const jerry_value_t func,
                        const jerry_value_t context,
                        const jerry_value_t* args,
                        const jerry_length_t length)
{
    printf("JSFlex::JsWidth-------\n");
    if (length < 1 || !jerry_value_is_number(args[0])) {
        return jerry_create_boolean(false);
    }

    double number = jerry_get_number_value(args[0]);

    if (number < static_cast<double>(std::numeric_limits<int16_t>::min()) ||
        number > static_cast<double>(std::numeric_limits<int16_t>::max())) {
        return jerry_create_boolean(false);
    }

    JsWidth(static_cast<int16_t>(number));

    return jerry_create_boolean(true);
}

jerry_value_t JSViewAbstract::JsSize(const jerry_value_t func,
                        const jerry_value_t context,
                        const jerry_value_t* args,
                        const jerry_length_t length)
{
    printf("JSFlex::JsSize-------\n");
    if (length < 2 || !jerry_value_is_number(args[0]) || !jerry_value_is_number(args[1])) {
        return jerry_create_boolean(false);
    }
 
    double width = jerry_get_number_value(args[0]);
    double height = jerry_get_number_value(args[1]);
 
    if (width < static_cast<double>(std::numeric_limits<int16_t>::min()) ||
        width > static_cast<double>(std::numeric_limits<int16_t>::max()) ||
        height < static_cast<double>(std::numeric_limits<int16_t>::min()) ||
        height > static_cast<double>(std::numeric_limits<int16_t>::max())) {
        return jerry_create_boolean(false);
    }
 
    JsWidth(static_cast<int16_t>(width));
    JsHeight(static_cast<int16_t>(height));

    return jerry_create_boolean(true);
}


void JSViewAbstract::JsWidth(const int16_t& val)
{
    ViewAbstractModel::GetInstance()->SetWidth(val);
}

void JSViewAbstract::JsHeight(const int16_t& val)
{

    ViewAbstractModel::GetInstance()->SetHeight(val);
}

bool JSViewAbstract::JsShowPage()
{
    return ViewAbstractModel::GetInstance()->ShowPage();
}   
}
}
