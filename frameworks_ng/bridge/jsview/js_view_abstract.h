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


#ifndef ARKUI_ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIGE_JSVIEW_JS_VIEW_ABSTRACT_H
#define ARKUI_ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIGE_JSVIEW_JS_VIEW_ABSTRACT_H

#include <iostream>
#include "jerryscript.h"
#include "gfx_utils/color.h"

namespace OHOS{
namespace ACELite {
using namespace std;
class JSViewAbstract {
public:
    static void JSBind();

    //for test
    static jerry_value_t JsShowPage(const jerry_value_t func,
                         const jerry_value_t context,
                         const jerry_value_t* args,
                         const jerry_length_t length);

    static jerry_value_t Pop(const jerry_value_t func,
                        const jerry_value_t context,
                        const jerry_value_t* args,
                        const jerry_length_t length);

    static jerry_value_t JsBackgroundColor(
                        const jerry_value_t func,
                        const jerry_value_t context,
                        const jerry_value_t* args,
                        const jerry_length_t length);      

    static jerry_value_t JsPadding(const jerry_value_t func,
                    const jerry_value_t context,
                    const jerry_value_t* args,
                    const jerry_length_t length);

    static jerry_value_t JsMargin(const jerry_value_t func,
                const jerry_value_t context,
                const jerry_value_t* args,
                const jerry_length_t length);       

    static jerry_value_t JsLayoutWeight(const jerry_value_t func,
                const jerry_value_t context,
                const jerry_value_t* args,
                const jerry_length_t length); 

    static jerry_value_t JsconstraintSize(const jerry_value_t func,
            const jerry_value_t context,
            const jerry_value_t* args,
            const jerry_length_t length); 

    static jerry_value_t JsHeight(const jerry_value_t func,
                         const jerry_value_t context,
                         const jerry_value_t* args,
                         const jerry_length_t length);

    static jerry_value_t JsWidth(const jerry_value_t func,
                         const jerry_value_t context,
                         const jerry_value_t* args,
                         const jerry_length_t length);

    static jerry_value_t JsSize(const jerry_value_t func,
                         const jerry_value_t context,
                         const jerry_value_t* args,
                         const jerry_length_t length);
                

    static void JsWidth(const int16_t& val);

    static void JsHeight(const int16_t& val);

    static bool JsShowPage();
private:
    static ColorType parseColor(const jerry_char_t* colorStr, jerry_size_t colorStrLen);


    static thread_local std::string className;

};

}
}
#endif
