/*
 * Copyright (c) 2020 Huawei Device Co., Ltd.
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

#include "presets/render_module.h"
#include "ace_log.h"
#include "component_factory.h"
#include "component_utils.h"
#include "directive/descriptor_utils.h"
#include "js_app_context.h"
#include "js_profiler.h"
namespace OHOS {
namespace ACELite {
const char * const RenderModule::FUNC_CREATE_ELEMENT = "_c";
const char * const RenderModule::FUNC_INIT_STYLE_SHEET = "initStyleSheet";
const char * const RenderModule::FUNC_LOOP_RENDER = "_l";
const char * const RenderModule::FUNC_CONDITIONAL_RENDER = "_i";
const int RenderModule::ARG_LENGTH_TAG_ONLY = 1;
const int RenderModule::ARG_LENGTH_WITHOUT_OPTIONS = 2;
const int RenderModule::ARG_LENGTH_WITH_OPTIONS = 3;
const int RenderModule::ARG_LENGTH_RENDER = 2;

void RenderModule::Init()
{
    CreateNamedFunction(FUNC_CREATE_ELEMENT, CreateElement);
    CreateNamedFunction(FUNC_LOOP_RENDER, LoopRender);
    CreateNamedFunction(FUNC_CONDITIONAL_RENDER, ConditionalRender);
    CreateNamedFunction(FUNC_INIT_STYLE_SHEET, InitStyleSheet);
}

jerry_value_t RenderModule::CreateElement(jerry_value_t tagName, jerry_value_t options, jerry_value_t children)
{
    JSValue viewModel = JSGlobal::Get(ATTR_ROOT);
    // check whether the current render element can be reused or not
    if (JSObject::Has(viewModel, "_renderList_")) {
        // get the current render component and update attributes and styles
        JSValue renderList = JSObject::Get(viewModel, "_renderList_");
        RenderInComponent(renderList, options, children);
        ReleaseJerryValue(renderList, viewModel, VA_ARG_END_FLAG);
        return UNDEFINED;
    }
    JSRelease(viewModel);
    uint16_t tagNameLength = 0;
    char *componentName = MallocStringOf(tagName, &tagNameLength);
    if (componentName == nullptr) {
        return UNDEFINED;
    }
    if (tagNameLength == 0) {
        ace_free(componentName);
        componentName = nullptr;
        return UNDEFINED;
    }

    uint16_t componentNameId = KeyParser::ParseKeyId(componentName, tagNameLength);
    ace_free(componentName);
    componentName = nullptr;

    // create component by tag name using factory
    Component *component = ComponentFactory::CreateComponent(componentNameId, options, children);
    if (component == nullptr) {
        // Release all children before we return UNDEFINED to avoid the children becoming ownerless in this case.
        HILOG_ERROR(HILOG_MODULE_ACE, "Fail to create element because the tag is not supported.");
        DescriptorUtils::ReleaseDescriptorOrElements(children);
        return UNDEFINED;
    }
    // add current component to component list
    viewModel = JSGlobal::Get(ATTR_ROOT);
    bool createResult = true;
    // check whether the current component is rendered in list for command
    if (JSObject::Has(viewModel, "_createList_")) {
        JSValue renderList = JSObject::Get(viewModel, "_createList_");
        List<Component *> *componentList = nullptr;
        if (!JSObject::GetNativePointer(renderList, reinterpret_cast<void **>(&componentList))) {
            HILOG_ERROR(HILOG_MODULE_ACE, "add component to create list failed");
            createResult = false;
        }
        // push the current component to the record component list
        componentList->PushBack(component);
        JSRelease(renderList);
    }
    JSRelease(viewModel);
    // component begin to render
    bool renderResult = component->Render();
    if (!renderResult || (!createResult)) {
        // render failed, drop this element by release its all children and itself
        DescriptorUtils::ReleaseDescriptorOrElements(children);
        component->Release();
        delete component;
        component = nullptr;
        return UNDEFINED;
    }

    // render successfully
    return component->GetNativeElement();
}

jerry_value_t RenderModule::CreateElement(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t *args,
                                          const jerry_length_t argsNum)
{
    jerry_value_t tagName;
    jerry_value_t options;
    jerry_value_t children;
    if (argsNum == ARG_LENGTH_WITH_OPTIONS) {
        tagName = args[0];
        options = args[1];
        const int8_t childrenNum = 2;
        children = args[childrenNum];
    } else if (argsNum == ARG_LENGTH_WITHOUT_OPTIONS) {
        tagName = args[0];
        if (jerry_value_is_array(args[1])) {
            options = UNDEFINED;
            children = args[1];
        } else {
            options = args[1];
            children = UNDEFINED;
        }
    } else if (argsNum == ARG_LENGTH_TAG_ONLY) {
        tagName = args[0];
        options = UNDEFINED;
        children = UNDEFINED;
    } else {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to create element cause by invalid arguments.");
        return UNDEFINED;
    }

    return CreateElement(tagName, options, children);
}

jerry_value_t RenderModule::InitStyleSheet(const jerry_value_t func,
                                           const jerry_value_t context,
                                           const jerry_value_t *args,
                                           const jerry_length_t argsNum)
{
    AppStyleManager *manager = const_cast<AppStyleManager *>(JsAppContext::GetInstance()->GetStyleManager());

    if (argsNum == 0 || manager == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to initialize style sheet cause by invalid arguments or empty manager!");
        return jerry_create_boolean(false);
    }
    START_TRACING(STYLESHEET_INIT);
    manager->InitStyleSheet(args[0]);
    STOP_TRACING();
    return jerry_create_boolean(true);
}

jerry_value_t RenderModule::LoopRender(const jerry_value_t func,
                                       const jerry_value_t context,
                                       const jerry_value_t *args,
                                       const jerry_length_t length)
{
    if (length != ARG_LENGTH_RENDER) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to LoopRender as the length of arguments invalid. Expect 2 but %d",
                    length);
        return UNDEFINED;
    }

    return DescriptorUtils::CreateForDescriptor(args[0], args[1]);
}

jerry_value_t RenderModule::ConditionalRender(const jerry_value_t func,
                                              const jerry_value_t context,
                                              const jerry_value_t *args,
                                              const jerry_length_t argsNum)
{
    if (argsNum != ARG_LENGTH_RENDER) {
        HILOG_ERROR(HILOG_MODULE_ACE, "Failed to ConditionalRender cause by invlaid paramters. Expect 2 but %d",
                    argsNum);
        return UNDEFINED;
    }

    return DescriptorUtils::CreateIfDescriptor(args[0], args[1]);
}

void RenderModule::RenderInComponent(JSValue renderList, JSValue options, JSValue children)
{
    if (JSUndefined::Is(renderList)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "the element is undefined");
        return;
    }
    ListNode<Component *> *currentComponent = nullptr;
    if (!JSObject::GetNativePointer(renderList, reinterpret_cast<void **>(&currentComponent))) {
        HILOG_ERROR(HILOG_MODULE_ACE, "get native element failed");
        return;
    }
    if (currentComponent->data_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "target component find failed");
        return;
    }
    // update watchers, styles and attributes
    currentComponent->data_->UpdateOptions(options);
    // switch to the next rendered component through component record list
    JSObject::SetNativePointer(renderList, currentComponent->next_);
}
} // namespace ACELite
} // namespace OHOS
