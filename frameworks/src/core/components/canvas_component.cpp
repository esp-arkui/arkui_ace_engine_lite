/*
 * Copyright (c) 2020-2021 Huawei Device Co., Ltd.
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

#include "acelite_config.h"

#ifdef FEATURE_COMPONENT_CANVAS
#include "canvas_component.h"
#include "js_fwk_common.h"
#include "product_adapter.h"
#include "securec.h"
#include "jerryscript.h"
#include "modules/presets/image_module.h"
#include "image_component.h"
namespace OHOS {
namespace ACELite {
// default fill style color=black
const char * const CanvasComponent::DEFAULT_FILLSTYLE = "#000000";
// default stroke style color=black
const char * const CanvasComponent::DEFAULT_STROKESTYLE = "#000000";
// default text align=left
const char * const CanvasComponent::DEFAULT_TEXTALIGN = "left";
// default line lineCap
const char * const CanvasComponent::DEFAULT_LINECAP = "butt";
// default line lineJoin
const char * const CanvasComponent::DEFAULT_LINEJOIN = "miter";
// default line lineJoin
const int16_t CanvasComponent::DEFAULT_MITERLIMIT = 10;
//default lineDashOffset
const int16_t CanvasComponent::DEFAULT_LINEDASHOFFSET = 0;

// API-attribute
const char * const CanvasComponent::ATTR_FILLSTYLE = "fillStyle";
const char * const CanvasComponent::ATTR_STROKESTYLE = "strokeStyle";
const char * const CanvasComponent::ATTR_LINEWIDTH = "lineWidth";
const char * const CanvasComponent::ATTR_FONT = "font";
const char * const CanvasComponent::ATTR_TEXTALIGN = "textAlign";
const char * const CanvasComponent::ATTR_LINECAP = "lineCap";
const char * const CanvasComponent::ATTR_LINEJOIN = "lineJoin";
const char * const CanvasComponent::ATTR_MITERLIMIT = "miterLimit";
const char * const CanvasComponent::ATTR_LINEDASHOFFSET = "lineDashOffset";
const char * const CanvasComponent::ATTR_GLOBALALPHA = "globalAlpha";
const char * const CanvasComponent::ATTR_GLOBALCOMPOSITEOPERATION = "globalCompositeOperation";
const char * const CanvasComponent::ATTR_SHADOWOFFSETX = "shadowOffsetX";
const char * const CanvasComponent::ATTR_SHADOWOFFSETY = "shadowOffsetY";
const char * const CanvasComponent::ATTR_SHADOWCOLOR = "shadowColor";
const char * const CanvasComponent::ATTR_SHADOWBLUR = "shadowBlur";
// API-method
const char * const CanvasComponent::FUNC_GETCONTEXT = "getContext";
const char * const CanvasComponent::FUNC_FILLRECT = "fillRect";
const char * const CanvasComponent::FUNC_STROKERECT = "strokeRect";
const char * const CanvasComponent::FUNC_FILLTEXT = "fillText";
const char * const CanvasComponent::FUNC_BEGINPATH = "beginPath";
const char * const CanvasComponent::FUNC_MOVETO = "moveTo";
const char * const CanvasComponent::FUNC_LINETO = "lineTo";
const char * const CanvasComponent::FUNC_RECT = "rect";
const char * const CanvasComponent::FUNC_CLEANRECT = "cleanRect";
const char * const CanvasComponent::FUNC_ARC = "arc";
const char * const CanvasComponent::FUNC_CLOSEPATH = "closePath";
const char * const CanvasComponent::FUNC_STROKE = "stroke";
const char * const CanvasComponent::FUNC_CREATELINEARGRADIENT = "createLinearGradient";
const char * const CanvasComponent::FUNC_CREATERADIALGRADIENT = "createRadialGradient";
const char * const CanvasComponent::FUNC_ADDCOLORSTOP = "addColorStop";
const char * const CanvasComponent::FUNC_CREATEPATTERN = "createPattern";
const char * const CanvasComponent::FUNC_FILL = "fill";
const char * const CanvasComponent::FUNC_DRAWIMAGE = "drawImage";
const char * const CanvasComponent::FUNC_SETLINEDASH = "setLineDash";
const char * const CanvasComponent::FUNC_GETLINEDASH = "getLineDash";
const char * const CanvasComponent::FUNC_STROKETEXT = "strokeText";
const char * const CanvasComponent::FUNC_ROTATE = "rotate";
const char * const CanvasComponent::FUNC_SCALE = "scale";
const char * const CanvasComponent::FUNC_MEASURETEXT = "measureText";
const char * const CanvasComponent::FUNC_TRANSLATE = "translate";
const char * const CanvasComponent::FUNC_TRANFORM = "transform";
const char * const CanvasComponent::FUNC_SETTRANFORM = "setTransform";
const char * const CanvasComponent::FUNC_SAVE = "save";
const char * const CanvasComponent::FUNC_RESTORE = "restore";
const char * const CanvasComponent::FUNC_DRAWCIRCLE = "drawCircle";
// create canvas draw attribute-callback mapping
const AttrMap CanvasComponent::attrMap_[] = {
    {ATTR_FILLSTYLE, FillStyleSetter, FillStyleGetter},
    {ATTR_STROKESTYLE, StrokeStyleSetter, StrokeStyleGetter},
    {ATTR_LINEWIDTH, LineWidthSetter, LineWidthGetter},
    {ATTR_FONT, FontSetter, FontGetter},
    {ATTR_TEXTALIGN, TextAlignSetter, TextAlignGetter},
    {ATTR_SHADOWOFFSETX, ShadowOffsetXSetter, ShadowOffsetXGetter},
    {ATTR_SHADOWOFFSETY, ShadowOffsetYSetter, ShadowOffsetYGetter},
    {ATTR_SHADOWCOLOR, ShadowColorSetter, ShadowColorGetter},
    {ATTR_SHADOWBLUR, ShadowBlurSetter, ShadowBlurGetter},
    {ATTR_LINECAP,LineCapSetter,LineCapGetter},
    {ATTR_LINEJOIN,LineJoinSetter,LineJoinGetter},
    {ATTR_MITERLIMIT,MiterLimitSetter,MiterLimitGetter},
    {ATTR_LINEDASHOFFSET,LineDashOffsetSetter,LineDashOffsetGetter},
    {ATTR_GLOBALALPHA, GlobalAlphaSetter, GlobalAlphaGetter},
    {ATTR_GLOBALCOMPOSITEOPERATION, GlobalCompositeOperationSetter, GlobalCompositeOperationGetter}
};

// create canvas draw method-callback mapping
const MethodMap CanvasComponent::methodMap_[] = {
    {FUNC_GETCONTEXT, GetContext},
    {FUNC_FILLRECT, FillRect},
    {FUNC_STROKERECT, StrokeRect},
    {FUNC_FILLTEXT, FillText},
    {FUNC_BEGINPATH, BeginPath},
    {FUNC_MOVETO, MoveTo},
    {FUNC_LINETO, LineTo},
    {FUNC_RECT, Rect},
    {FUNC_CLEANRECT, CleanRect},
    {FUNC_ARC, Arc},
    {FUNC_CLOSEPATH, ClosePath},
    {FUNC_STROKE, Stroke},
    {FUNC_CREATELINEARGRADIENT, CreateLInearGradient},
    {FUNC_CREATERADIALGRADIENT, CreateRadialGradient},
    {FUNC_ADDCOLORSTOP, AddColorStop},
    {FUNC_CREATEPATTERN, CreatePattern},
    {FUNC_FILL, Fill},
    {FUNC_DRAWIMAGE,DrawImage},
    {FUNC_SETLINEDASH, SetLineDash},
    {FUNC_GETLINEDASH, GetLineDash},
    {FUNC_STROKETEXT, StrokeText},
    {FUNC_ROTATE, Rotate},
    {FUNC_SCALE, Scale},
    {FUNC_MEASURETEXT, MeasureText},
    {FUNC_TRANSLATE, Translate},
    {FUNC_TRANFORM, Transform},
    {FUNC_SETTRANFORM, SetTransform},
    {FUNC_SAVE, Save},
    {FUNC_RESTORE, Restore},
    {FUNC_DRAWCIRCLE, DrawCircle}
};

CanvasComponent::CanvasComponent(jerry_value_t options, jerry_value_t children, AppStyleManager *styleManager)
    : Component(options, children, styleManager),
      context_(UNDEFINED),
      dashArray_(UNDEFINED),
	  measureTextObject_(UNDEFINED),
      measureTextWidthString_(UNDEFINED),
      fillStyleValue_(nullptr),
      strokeStyleValue_(nullptr),
      fontValue_(nullptr),
      textAlignValue_(nullptr),
      shadowOffsetXValue_(0),
      shadowOffsetYValue_(0),
      shadowBlurValue_(0),
      shadowColorValue_(nullptr),
      lineWidthValue_(1),
      lineCapValue_(nullptr),
      lineJoinValue_(nullptr),
      miterLimitValue_(DEFAULT_MITERLIMIT),
      lineDashOffsetValue_(0),
      colorStopValue_(nullptr),
      patternPathValue_(nullptr),
      patternRepeatTypeValue_(nullptr)
{
    SetComponentName(K_CANVAS);
    // set default paint pattern
    paint_.SetFillColor(Color::Black());
    paint_.SetOpacity(OPA_OPAQUE);
    paint_.SetStrokeColor(Color::Black());
    paint_.SetStrokeWidth(1);

    // set default text font pattern
    fontStyle_.align = TEXT_ALIGNMENT_LEFT;
    fontStyle_.direct = TEXT_DIRECT_LTR;
    fontStyle_.fontSize = ProductAdapter::GetDefaultFontSize();
    char *defaultFontName = nullptr;
    CopyFontFamily(defaultFontName, ProductAdapter::GetDefaultFontFamilyName());
    fontStyle_.fontName = defaultFontName;
    fontStyle_.letterSpace = DEFAULT_FONT_LETTERSPACE;
	canvas_.SetDrawGraphicsContext(paint_);
    RegisterNamedFunction(methodMap_[0].methodName, methodMap_[0].callbackName);
}

// Create UICanvas
bool CanvasComponent::CreateNativeViews()
{
    return true;
}

void CanvasComponent::ReleaseNativeViews()
{
    ACE_FREE(fillStyleValue_);
    ACE_FREE(strokeStyleValue_);
    ACE_FREE(fontValue_);
    ACE_FREE(textAlignValue_);
	ACE_FREE(lineCapValue_);
    ACE_FREE(lineJoinValue_);
    // free fontStyle_.fontName memory which malloc in FontSetter method.
    if (fontStyle_.fontName != nullptr) {
        ace_free(const_cast<char *>(fontStyle_.fontName));
        fontStyle_.fontName = nullptr;
    }
    if (!IS_UNDEFINED(context_)) {
        bool deleted = jerry_delete_object_native_pointer(context_, nullptr);
        if (!deleted) {
            HILOG_WARN(HILOG_MODULE_ACE, "canvas_component: delete object native pointer context_ failed!");
        }
        jerry_release_value(context_);
	}
    if (!IS_UNDEFINED(dashArray_)) {
        uint32_t length = jerry_get_array_length(dashArray_);
        for (uint32_t i =0; i < length; i++) {
            jerry_value_t val = jerry_get_property_by_index(dashArray_, i);
            jerry_release_value(val);
        }
        jerry_release_value(dashArray_);
    }
	if (!IS_UNDEFINED(jerry_get_property(measureTextObject_, measureTextWidthString_))) {
        jerry_release_value(jerry_get_property(measureTextObject_, measureTextWidthString_));
    }
    if (!IS_UNDEFINED(measureTextWidthString_)) {
        jerry_release_value(measureTextWidthString_);
    }
    if (!IS_UNDEFINED(measureTextObject_)) {
        jerry_release_value(measureTextObject_);
    }

	
}

UIView *CanvasComponent::GetComponentRootView() const
{
    return (const_cast<UICanvas *>(&canvas_));
}

jerry_value_t CanvasComponent::GetContext(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of getContext method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("getContext method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    if (IS_UNDEFINED(component->context_)) {
        component->context_ = jerry_create_object();
        jerry_set_object_native_pointer(component->context_, component, nullptr);

        // register fillStyle, strokeStyle, lineWidth, font, textAlign attribute
        uint16_t attrMapLength = sizeof(attrMap_) / sizeof(attrMap_[0]);
        for (uint16_t index = 0; index < attrMapLength; index++) {
            RegisterAttributeFunc(component->context_, attrMap_[index].attrName, attrMap_[index].setterName,
                                  attrMap_[index].getterName);
        }

        // register fillRect, strokeRect, fillText, beginPath, moveTo, lineTo, rect, arc, closePath, stroke method
        uint16_t methodMapLength = sizeof(methodMap_) / sizeof(methodMap_[0]);
        for (uint16_t index = 1; index < methodMapLength; index++) {
            RegisterDrawMethodFunc(component->context_, methodMap_[index].methodName, methodMap_[index].callbackName);
        }
    }

    // BeginPath function need to be called after getting canvas API object
    component->canvas_.BeginPath();

    jerry_acquire_value(component->context_);
    return component->context_;
}

jerry_value_t CanvasComponent::FillStyleSetter(const jerry_value_t func,
                                               const jerry_value_t context,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: fillStyle value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("fillStyle value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->fillStyleValue_);
    uint16_t fillStyleLength = 0;
    component->fillStyleValue_ = MallocStringOf(args[ArgsIndex::IDX_0], &fillStyleLength);
    if (component->fillStyleValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: fillStyle value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("fillStyle value erro!"));
    }

    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    uint16_t fillStyleId = KeyParser::ParseKeyId(component->fillStyleValue_, fillStyleLength);
    if (fillStyleId == K_CANVASPATTERN) {
        component->paint_.SetStyle(Paint::PaintStyle::PATTERN);
        return UNDEFINED;
    }
    if (fillStyleId == K_CANVASGRADIENT) {
        component->paint_.SetStyle(Paint::PaintStyle::FILL_GRADIENT);
        component->paint_.FillStyle(component->gradientControl_);
    }
    if(ParseColor(component->fillStyleValue_, color, alpha)){
        component->paint_.SetFillColor(component->GetRGBColor(color));
        component->paint_.SetOpacity(alpha);
    }
    return UNDEFINED;
}

jerry_value_t CanvasComponent::FillStyleGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    if (component->fillStyleValue_ == nullptr) {
        CopyFontFamily(component->fillStyleValue_, DEFAULT_FILLSTYLE);
    }

    if (component->fillStyleValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->fillStyleValue_));
    }
    return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("fillStyle value error"));
}

jerry_value_t CanvasComponent::StrokeStyleSetter(const jerry_value_t func,
                                                 const jerry_value_t context,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: strokeStyle value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("the value of strokeStyle is null"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->strokeStyleValue_);
    uint16_t strokeStyleLength = 0;
    component->strokeStyleValue_ = MallocStringOf(args[ArgsIndex::IDX_0], &strokeStyleLength);
    if (component->strokeStyleValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: strokeStyle value error");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("strokeStyle value error"));
    }

    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    uint16_t strokeStyleId = KeyParser::ParseKeyId(component->strokeStyleValue_, strokeStyleLength);
    if (strokeStyleId == K_CANVASPATTERN) {
        component->paint_.SetStyle(Paint::PaintStyle::PATTERN);
        return UNDEFINED;
    }
    if (strokeStyleId == K_CANVASGRADIENT) {
        component->paint_.SetStyle(Paint::PaintStyle::STROKE_GRADIENT);
        return UNDEFINED;
    }
    if (ParseColor(component->strokeStyleValue_, color, alpha)) {
        component->paint_.SetStrokeColor(component->GetRGBColor(color));
        component->paint_.SetOpacity(alpha);
    }
    return UNDEFINED;
}

jerry_value_t CanvasComponent::StrokeStyleGetter(const jerry_value_t func,
                                                 const jerry_value_t dom,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    if (component->strokeStyleValue_ == nullptr) {
        CopyFontFamily(component->strokeStyleValue_, DEFAULT_STROKESTYLE);
    }

    if (component->strokeStyleValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->strokeStyleValue_));
    }
    return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("strokeStyle value error"));
}

jerry_value_t CanvasComponent::LineWidthSetter(const jerry_value_t func,
                                               const jerry_value_t context,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineWidth value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineWidth value error!"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    component->lineWidthValue_ = IntegerOf(args[ArgsIndex::IDX_0]);
    component->paint_.SetStrokeWidth(component->lineWidthValue_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::LineWidthGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    return jerry_create_number(component->lineWidthValue_);
}

jerry_value_t CanvasComponent::FontSetter(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: font value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("font value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->fontValue_);

    component->fontValue_ = MallocStringOf(args[ArgsIndex::IDX_0]);
    if (component->fontValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: text font value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("text font value error"));
    }

    const int8_t maxParamCount = 2;
    for (int8_t index = 0; index < maxParamCount; index++) {
        // get font size or font family from fontValue.
        char *mallocSubFont = nullptr;
        component->GetSubFont(component->fontValue_, index, mallocSubFont);
        if (mallocSubFont == nullptr) {
            HILOG_WARN(HILOG_MODULE_ACE, "canvas_component: get text font size or font family failed");
            ace_free(component->fontValue_);
            component->fontValue_ = nullptr;
            return UNDEFINED;
        }

        // if it is a font size
        if (*mallocSubFont >= '0' && *mallocSubFont <= '9') {
            component->fontStyle_.fontSize = strtol(mallocSubFont, nullptr, DEC);
            ace_free(mallocSubFont);
            mallocSubFont = nullptr;
        } else { // if it is a font family
            // free default component->fontStyle_.fontName memory.
            if (component->fontStyle_.fontName != nullptr) {
                ace_free(const_cast<char *>(component->fontStyle_.fontName));
                component->fontStyle_.fontName = nullptr;
            }
            // set customized font name, the memory of mallocFontFamily need be free in CanvasFillText method.
            component->fontStyle_.fontName = mallocSubFont;
        }
    }
    return UNDEFINED;
}

jerry_value_t CanvasComponent::FontGetter(const jerry_value_t func,
                                          const jerry_value_t dom,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    if (component->fontValue_ == nullptr) {
        uint8_t defaultFontSize = ProductAdapter::GetDefaultFontSize();
        const char *defaultFontName = ProductAdapter::GetDefaultFontFamilyName();
        size_t nameLength = (defaultFontName != nullptr) ? strlen(defaultFontName) : 0;
        const uint8_t maxNameLen = 32;
        const uint8_t maxFontSizeLen = 16;
        const uint8_t maxBufferLen = maxNameLen + maxFontSizeLen;
        if (nameLength > 0 && (nameLength < maxNameLen) && (defaultFontSize < UINT8_MAX)) {
            char defaultFont[maxBufferLen] = {0};
            int length = sprintf_s(defaultFont, (maxBufferLen - 1), "%dpx %s", defaultFontSize, defaultFontName);
            if (length > 0 && length < maxBufferLen) {
                CopyFontFamily(component->fontValue_, defaultFont, length);
            }
        }
    }

    if (component->fontValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->fontValue_));
    }
    return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("text font value error"));
}

jerry_value_t CanvasComponent::TextAlignSetter(const jerry_value_t func,
                                               const jerry_value_t context,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: textAlign value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("textAlign value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->textAlignValue_);

    uint16_t textAlignLength = 0;
    component->textAlignValue_ = MallocStringOf(args[ArgsIndex::IDX_0], &textAlignLength);
    if (component->textAlignValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: text align value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("text align value error"));
    }

    uint16_t textAlignId = KeyParser::ParseKeyId(component->textAlignValue_, textAlignLength);
    if (textAlignId == K_LEFT) {
        component->fontStyle_.align = TEXT_ALIGNMENT_LEFT;
    } else if (textAlignId == K_RIGHT) {
        component->fontStyle_.align = TEXT_ALIGNMENT_RIGHT;
    } else if (textAlignId == K_CENTER) {
        component->fontStyle_.align = TEXT_ALIGNMENT_CENTER;
    } else {
        // do nothing(use default align=TEXT_ALIGNMENT_LEFT)
    }
    return UNDEFINED;
}

jerry_value_t CanvasComponent::TextAlignGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    if (component->textAlignValue_ == nullptr) {
        CopyFontFamily(component->textAlignValue_, DEFAULT_TEXTALIGN);
    }

    if (component->textAlignValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->textAlignValue_));
    }
    return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("textAlign value error"));
}

jerry_value_t CanvasComponent::ShadowOffsetXSetter(const jerry_value_t func,
                                                   const jerry_value_t context,
                                                   const jerry_value_t *args,
                                                   const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: shadowOffsetX value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("shadowOffsetX value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    component->shadowOffsetXValue_ = IntegerOf(args[ArgsIndex::IDX_0]);
    component->paint_.SetShadowOffsetX(component->shadowOffsetXValue_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::ShadowOffsetXGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    return jerry_create_number(component->shadowOffsetXValue_);
}

jerry_value_t CanvasComponent::ShadowOffsetYSetter(const jerry_value_t func,
                                                   const jerry_value_t context,
                                                   const jerry_value_t *args,
                                                   const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: shadowOffsetY value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("shadowOffsetY value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    component->shadowOffsetYValue_ = IntegerOf(args[ArgsIndex::IDX_0]);
    component->paint_.SetShadowOffsetY(component->shadowOffsetYValue_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::ShadowOffsetYGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    return jerry_create_number(component->shadowOffsetYValue_);
}

jerry_value_t CanvasComponent::ShadowBlurSetter(const jerry_value_t func,
                                                   const jerry_value_t context,
                                                   const jerry_value_t *args,
                                                   const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: shadowBlur value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("shadowBlur value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    component->shadowBlurValue_ = IntegerOf(args[ArgsIndex::IDX_0]);
    component->paint_.SetShadowBlurRadius(component->shadowBlurValue_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::ShadowBlurGetter(const jerry_value_t func,
                                               const jerry_value_t dom,
                                               const jerry_value_t args[],
                                               const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    return jerry_create_number(component->shadowBlurValue_);
}

jerry_value_t CanvasComponent::ShadowColorSetter(const jerry_value_t func,
                                                 const jerry_value_t context,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: shadowColor value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("shadowColor value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->shadowColorValue_);

    component->shadowColorValue_ = MallocStringOf(args[ArgsIndex::IDX_0]);
    if (component->shadowColorValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: shadowColor value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("shadowColor value erro!"));
    }

    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    ParseColor(component->shadowColorValue_, color, alpha);
    ColorType shadowColor = component->GetRGBColor(color);
    shadowColor.alpha = alpha;
    component->paint_.SetShadowColor(shadowColor);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::ShadowColorGetter(const jerry_value_t func,
                                                 const jerry_value_t dom,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    if (component->shadowColorValue_ == nullptr) {
        CopyFontFamily(component->shadowColorValue_, DEFAULT_FILLSTYLE);
    }

    if (component->shadowColorValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->shadowColorValue_));
    }
    return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("shadowColor value error"));
}
jerry_value_t CanvasComponent::LineCapSetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineCap value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("lineCap value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->lineCapValue_);

    uint16_t length = 0;
    component->lineCapValue_ = MallocStringOf(args[ArgsIndex::IDX_0], &length);
    if (component->lineCapValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineCap value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineCap value error"));
    }

    uint8_t lineCap = ParseLineCap(component->lineCapValue_);
    component->paint_.SetLineCap((BaseGfxExtendEngine::LineCap)lineCap);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::LineCapGetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    if (component->lineCapValue_ == nullptr) {
        CopyFontFamily(component->lineCapValue_, DEFAULT_LINECAP);
    }
    if (component->lineCapValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->lineCapValue_));
    }
    return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineCap value error"));
}

jerry_value_t CanvasComponent::LineJoinSetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineCap value error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("lineCap value error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->lineJoinValue_);

    uint16_t length = 0;
    component->lineJoinValue_ = MallocStringOf(args[ArgsIndex::IDX_0], &length);
    if (component->lineJoinValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineJoin value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineJoin value error"));
    }

    uint8_t lineJoin = ParseLineJoin(component->lineJoinValue_);
    component->paint_.SetLineJoin((BaseGfxExtendEngine::LineJoin)lineJoin);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::LineJoinGetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    if (component->lineJoinValue_ == nullptr) {
        CopyFontFamily(component->lineJoinValue_, DEFAULT_LINEJOIN);
    }
    if (component->lineJoinValue_ != nullptr) {
        return jerry_create_string(reinterpret_cast<const jerry_char_t *>(component->lineJoinValue_));
    }
    return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineJoin value error"));
}

jerry_value_t CanvasComponent::MiterLimitSetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: miterLimit value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineWidth value error!"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    if(jerry_value_is_number(args[ArgsIndex::IDX_0])){
        component->miterLimitValue_ = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    }else if(jerry_value_is_string(args[ArgsIndex::IDX_0])){
        char* value = MallocStringOf(args[ArgsIndex::IDX_0]);
        component->miterLimitValue_ = atof(value);
        ACE_FREE(value);
    }
    component->paint_.SetMiterLimit(component->miterLimitValue_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::MiterLimitGetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    return jerry_create_number(component->miterLimitValue_);
}

jerry_value_t CanvasComponent::LineDashOffsetSetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineWidth value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineWidth value error!"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    if(jerry_value_is_number(args[ArgsIndex::IDX_0])){
        component->lineDashOffsetValue_ = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    }else if(jerry_value_is_string(args[ArgsIndex::IDX_0])){
        char* value = MallocStringOf(args[ArgsIndex::IDX_0]);
        component->lineDashOffsetValue_ = atof(value);
        ACE_FREE(value);
    }

    component->paint_.SetLineDashOffset(component->lineDashOffsetValue_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::LineDashOffsetGetter(const jerry_value_t func, const jerry_value_t contex, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(contex));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    return jerry_create_number(component->lineDashOffsetValue_);
}

jerry_value_t CanvasComponent::GlobalAlphaSetter(const jerry_value_t func,
                                                 const jerry_value_t context,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineWidth value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineWidth value error!"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    double globalAlpha = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    component->canvas_.GlobalAlpha(globalAlpha, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::GlobalAlphaGetter(const jerry_value_t func,
                                                 const jerry_value_t dom,
                                                 const jerry_value_t args[],
                                                 const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    return jerry_create_number(component->paint_.GetGlobalAlpha());
}

jerry_value_t CanvasComponent::GlobalCompositeOperationSetter(const jerry_value_t func,
                                                              const jerry_value_t context,
                                                              const jerry_value_t args[],
                                                              const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: lineWidth value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("lineWidth value error!"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    char *globalCompositeOperation = MallocStringOf(args[ArgsIndex::IDX_0]);
    if (globalCompositeOperation == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get text value failed");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("get text value failed"));
    }

    if (strcmp(globalCompositeOperation, "source-over") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_SRC_OVER);
    } else if (strcmp(globalCompositeOperation, "source-atop") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_SRC_ATOP);
    } else if (strcmp(globalCompositeOperation, "source-in") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_SRC_IN);
    } else if (strcmp(globalCompositeOperation, "source-out") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_SRC_OUT);
    } else if (strcmp(globalCompositeOperation, "destination-over") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_DST_OVER);
    } else if (strcmp(globalCompositeOperation, "destination-atop") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_DST_ATOP);
    } else if (strcmp(globalCompositeOperation, "destination-in") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_DST_IN);
    } else if (strcmp(globalCompositeOperation, "destination-out") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_DST_OUT);
    } else if (strcmp(globalCompositeOperation, "lighter") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_LIGHTEN);
    } else if (strcmp(globalCompositeOperation, "copy") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_COPY);
    } else if (strcmp(globalCompositeOperation, "xor") == 0) {
        component->paint_.SetGlobalCompositeOperation(OHOS::BlendMode::BLEND_XOR);
    }

    ACE_FREE(globalCompositeOperation);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::GlobalCompositeOperationGetter(const jerry_value_t func,
                                                              const jerry_value_t dom,
                                                              const jerry_value_t args[],
                                                              const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(dom));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int8_t globalCompositeOperation = component->paint_.GetGlobalCompositeOperation();
    return jerry_create_number(globalCompositeOperation);

}

jerry_value_t CanvasComponent::FillRect(const jerry_value_t func,
                                        const jerry_value_t context,
                                        const jerry_value_t args[],
                                        const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_4) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of fillRect method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("fillRect method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t startX = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t startY = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t width = IntegerOf(args[ArgsIndex::IDX_2]);
    int16_t height = IntegerOf(args[ArgsIndex::IDX_3]);

    // FILL_STYLE: fill rect support fill shapses only
    component->paint_.SetStyle(component->paint_.FILL_STYLE);

    Point startPoint;
    startPoint.x = startX;
    startPoint.y = startY;
    component->canvas_.DrawRect(startPoint, height, width, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::StrokeRect(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_4) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of strokeRect method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("strokeRect method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t startX = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t startY = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t width = IntegerOf(args[ArgsIndex::IDX_2]);
    int16_t height = IntegerOf(args[ArgsIndex::IDX_3]);

    // STROKE_STYLE: stroke rect support draw borders only
    component->paint_.SetStyle(component->paint_.STROKE_STYLE);

    Point startPoint;
    startPoint.x = startX;
    startPoint.y = startY;
    //component->canvas_.DrawRect(startPoint, height, width, component->paint_);
	component->canvas_.StrokeRect(startPoint, height, width, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::FillText(const jerry_value_t func,
                                        const jerry_value_t context,
                                        const jerry_value_t args[],
                                        const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_3) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of fillText method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("fillText method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    char *textValue = MallocStringOf(args[ArgsIndex::IDX_0]);
    if (textValue == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get text value failed");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("get text value failed"));
    }

    int16_t startX = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t startY = IntegerOf(args[ArgsIndex::IDX_2]);
    int16_t maxWidth = component->canvas_.GetWidth();

    // FILL_STYLE: fillText support fill shapses only
    component->paint_.SetStyle(component->paint_.FILL_STYLE);

    Point startPoint;
    const int8_t half = 2;
    startPoint.x = startX;
    startPoint.y = startY;

    // if textAlign=left, not need transfer startX, if textAlign=right or center, need transfer startX
    if (component->fontStyle_.align == TEXT_ALIGNMENT_RIGHT) {
        startPoint.x = startX - maxWidth;
    } else if (component->fontStyle_.align == TEXT_ALIGNMENT_CENTER) {
        startPoint.x = (startX + startX - maxWidth) / half;
    } else {
        startPoint.x = startX;
    }

    component->canvas_.DrawLabel(startPoint, textValue, maxWidth, component->fontStyle_, component->paint_);

    ACE_FREE(textValue);
    return UNDEFINED;
}


jerry_value_t CanvasComponent::StrokeText(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_5) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of strokeText method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("strokeText method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    char *textValue = MallocStringOf(args[ArgsIndex::IDX_0]);
    if (textValue == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get text value failed");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("get text value failed"));
    }

    int16_t startX = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t startY = IntegerOf(args[ArgsIndex::IDX_2]);
    int16_t maxWidth = component->canvas_.GetWidth();

    // FILL_STYLE: strokeText support fill shapses only
    component->paint_.SetStyle(component->paint_.FILL_STYLE);

    Point startPoint;
    const int8_t half = 2;
    startPoint.x = startX;
    startPoint.y = startY;

    // if textAlign=left, not need transfer startX, if textAlign=right or center, need transfer startX
    if (component->fontStyle_.align == TEXT_ALIGNMENT_RIGHT) {
        startPoint.x = startX - maxWidth;
    } else if (component->fontStyle_.align == TEXT_ALIGNMENT_CENTER) {
        startPoint.x = (startX + startX - maxWidth) / half;
    } else {
        startPoint.x = startX;
    }

    component->canvas_.StrokeText(textValue, startPoint, component->fontStyle_, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::Rotate(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t args[],
                                      const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of rotate method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("rotate method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    double angle = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    component->canvas_.SetRotate(angle, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::Scale(const jerry_value_t func,
                                     const jerry_value_t context,
                                     const jerry_value_t args[],
                                     const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_2) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of scale method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("scale method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    double scaleX = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    double scaleY = jerry_get_number_value(args[ArgsIndex::IDX_1]);
    component->canvas_.SetScale(scaleX, scaleY, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::MeasureText(const jerry_value_t func,
                                           const jerry_value_t context,
                                           const jerry_value_t args[],
                                           const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of measureText method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("measureText method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    char *textValue = MallocStringOf(args[ArgsIndex::IDX_0]);
    if (textValue == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get text value failed");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("get text value failed"));
    }

    if (IS_UNDEFINED(component->measureTextObject_)) {
        component->measureTextObject_ = jerry_create_object();
    }
    if (IS_UNDEFINED(component->measureTextWidthString_)) {
        component->measureTextWidthString_ = jerry_create_string(reinterpret_cast<const jerry_char_t *>("width"));
    }
    Point ponit = component->canvas_.MeasureText(textValue, component->fontStyle_, component->paint_);
    jerry_set_property(component->measureTextObject_, component->measureTextWidthString_, ponit.x);

    ACE_FREE(textValue);
    return component->measureTextObject_;
}

jerry_value_t CanvasComponent::Translate(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_2) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of translate method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("translate method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t positionX = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t positionY = IntegerOf(args[ArgsIndex::IDX_1]);

    component->canvas_.SetTranslate(positionX, positionY, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::Transform(const jerry_value_t func,
                                         const jerry_value_t context,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_6) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of rotate method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("rotate method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    double scaleX = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    double shearY = jerry_get_number_value(args[ArgsIndex::IDX_1]);
    double shearX = jerry_get_number_value(args[ArgsIndex::IDX_2]);
    double scaleY = jerry_get_number_value(args[ArgsIndex::IDX_3]);
    double translateX = jerry_get_number_value(args[ArgsIndex::IDX_4]);
    double translateY = jerry_get_number_value(args[ArgsIndex::IDX_5]);
    component->canvas_.Transform(scaleX, shearY, shearX, scaleY, translateX, translateY, component->paint_);
    return UNDEFINED;
}


jerry_value_t CanvasComponent::SetTransform(const jerry_value_t func,
                                            const jerry_value_t context,
                                            const jerry_value_t args[],
                                            const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_6) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of rotate method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("rotate method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    double scaleX = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    double shearY = jerry_get_number_value(args[ArgsIndex::IDX_1]);
    double shearX = jerry_get_number_value(args[ArgsIndex::IDX_2]);
    double scaleY = jerry_get_number_value(args[ArgsIndex::IDX_3]);
    double translateX = jerry_get_number_value(args[ArgsIndex::IDX_4]);
    double translateY = jerry_get_number_value(args[ArgsIndex::IDX_5]);
    component->canvas_.SetTransform(scaleX, shearY, shearX, scaleY, translateX, translateY, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::Save(const jerry_value_t func,
                                    const jerry_value_t context,
                                    const jerry_value_t args[],
                                    const jerry_length_t argsNum)
{
    (void)func;

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    component->canvas_.Save(component->paint_);

    return UNDEFINED;
}

jerry_value_t CanvasComponent::Restore(const jerry_value_t func,
                                       const jerry_value_t context,
                                       const jerry_value_t args[],
                                       const jerry_length_t argsNum)
{
    (void)func;

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    component->paint_ = component->canvas_.Restore();
    return UNDEFINED;

}


jerry_value_t CanvasComponent::DrawCircle(const jerry_value_t func,
                                          const jerry_value_t context,
                                          const jerry_value_t args[],
                                          const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_3) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of arc method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("arc method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t centerX = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t centerY = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t radius = IntegerOf(args[ArgsIndex::IDX_2]);

    Point centerPoint;
    centerPoint.x = centerX;
    centerPoint.y = centerY;

    component->canvas_.DrawCircle(centerPoint, radius, component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::BeginPath(const jerry_value_t func,
                                         const jerry_value_t context,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    component->canvas_.BeginPath();
    return UNDEFINED;
}

jerry_value_t CanvasComponent::MoveTo(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t args[],
                                      const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_2) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of moveTo method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("moveTo method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t x = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t y = IntegerOf(args[ArgsIndex::IDX_1]);

    Point point;
    point.x = x;
    point.y = y;
    component->canvas_.MoveTo(point);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::LineTo(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t args[],
                                      const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_2) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of lineTo method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("lineTo method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t x = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t y = IntegerOf(args[ArgsIndex::IDX_1]);

    Point point;
    point.x = x;
    point.y = y;
    component->canvas_.LineTo(point);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::Rect(const jerry_value_t func,
                                    const jerry_value_t context,
                                    const jerry_value_t args[],
                                    const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_4) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of rect method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("rect method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t x = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t y = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t width = IntegerOf(args[ArgsIndex::IDX_2]);
    int16_t height = IntegerOf(args[ArgsIndex::IDX_3]);

    Point point;
    point.x = x;
    point.y = y;
    component->canvas_.AddRect(point, height, width);
    return UNDEFINED;
}


jerry_value_t CanvasComponent::CleanRect(const jerry_value_t func, const jerry_value_t context, const jerry_value_t args[], const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_4) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of rect method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("rect method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t x = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t y = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t width = IntegerOf(args[ArgsIndex::IDX_2]);
    int16_t height = IntegerOf(args[ArgsIndex::IDX_3]);

    Point point;
    point.x = x;
    point.y = y;
    component->canvas_.ClearRect(point, height, width, component->paint_);
    return UNDEFINED;
}
jerry_value_t CanvasComponent::Arc(const jerry_value_t func,
                                   const jerry_value_t context,
                                   const jerry_value_t args[],
                                   const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_5 && argsNum != ArgsCount::NUM_6) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of arc method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("arc method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    int16_t centerX = IntegerOf(args[ArgsIndex::IDX_0]);
    int16_t centerY = IntegerOf(args[ArgsIndex::IDX_1]);
    int16_t radius = IntegerOf(args[ArgsIndex::IDX_2]);
    double sAngle = jerry_get_number_value(args[ArgsIndex::IDX_3]);
    double eAngle = jerry_get_number_value(args[ArgsIndex::IDX_4]);

    bool counterClockwise = false;
    if (argsNum == ArgsCount::NUM_6) {
        if (jerry_value_is_boolean(args[ArgsIndex::IDX_5])) {
            counterClockwise = BoolOf(args[ArgsIndex::IDX_5]);
        }
    }

    Point centerPoint;
    centerPoint.x = centerX;
    centerPoint.y = centerY;
    int16_t startAngle = 0;
    int16_t endAngle = 0;

    bool result = component->FormatArcAngle(sAngle, eAngle, startAngle, endAngle, counterClockwise);
    if (!result) {
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("arc angle error"));
    }

    // 0 degree is at the 3 o'clock position of the arc's circle at JS layer,
    // but which is at the 12 o'clock position at Native layer.
    constexpr int16_t DEGREES_OFFSET = 90;
    constexpr int16_t DEGREES_360 = 360;
    if (((startAngle + DEGREES_OFFSET) <= INT16_MAX) && ((endAngle + DEGREES_OFFSET) <= INT16_MAX)) {
        startAngle = startAngle + DEGREES_OFFSET;
        endAngle = endAngle + DEGREES_OFFSET;
    } else {
        startAngle = startAngle + DEGREES_OFFSET - DEGREES_360;
        endAngle = endAngle + DEGREES_OFFSET - DEGREES_360;
    }

    component->canvas_.ArcTo(centerPoint, radius, startAngle, endAngle);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::ClosePath(const jerry_value_t func,
                                         const jerry_value_t context,
                                         const jerry_value_t args[],
                                         const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    component->canvas_.ClosePath();
    return UNDEFINED;
}

jerry_value_t CanvasComponent::Stroke(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t args[],
                                      const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    if (component->paint_.GetStyle() == Paint::PaintStyle::PATTERN) {
        component->canvas_.StrokePattern(component->paint_);
        return UNDEFINED;
    }
    if (component->paint_.GetStyle() == Paint::PaintStyle::STROKE_GRADIENT) {
        component->canvas_.Gradient(component->paint_);
        return UNDEFINED;
    }
    component->canvas_.DrawPath(component->paint_);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::CreateLInearGradient(const jerry_value_t func,
                                                    const jerry_value_t context,
                                                    const jerry_value_t args[],
                                                    const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_4 ) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of createLinearGradient method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("createLinearGradient method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    double startX = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    double startY = jerry_get_number_value(args[ArgsIndex::IDX_1]);
    double endX = jerry_get_number_value(args[ArgsIndex::IDX_2]);
    double endY = jerry_get_number_value(args[ArgsIndex::IDX_3]);


    component->gradientControl_.createLinearGradient(startX, startY, endX, endY);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::CreateRadialGradient(const jerry_value_t func,
                                                    const jerry_value_t context,
                                                    const jerry_value_t args[],
                                                    const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_6 ) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of createRadialGradient method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("createRadialGradient method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    double startX = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    double startY = jerry_get_number_value(args[ArgsIndex::IDX_1]);
    double startR = jerry_get_number_value(args[ArgsIndex::IDX_2]);
    double endX = jerry_get_number_value(args[ArgsIndex::IDX_3]);
    double endY = jerry_get_number_value(args[ArgsIndex::IDX_4]);
    double endR = jerry_get_number_value(args[ArgsIndex::IDX_5]);


    component->gradientControl_.createRadialGradient(startX, startY, startR, endX, endY, endR);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::AddColorStop(const jerry_value_t func,
                                            const jerry_value_t context,
                                            const jerry_value_t args[],
                                            const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_2) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of addColorStop method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("addColorStop method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->colorStopValue_);
    double stop = jerry_get_number_value(args[ArgsIndex::IDX_0]);
    component->colorStopValue_ = MallocStringOf(args[ArgsIndex::IDX_1]);
    if (component->colorStopValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: colorStop value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("colorStop value erro!"));
    }

    uint32_t color = 0;
    uint8_t alpha = OPA_OPAQUE;
    ParseColor(component->colorStopValue_, color, alpha);
    ColorType colorStop = component->GetRGBColor(color);
    colorStop.alpha = alpha;
    component->gradientControl_.addColorStop(stop, colorStop);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::CreatePattern(const jerry_value_t func,
                                             const jerry_value_t context,
                                             const jerry_value_t args[],
                                             const jerry_length_t argsNum)
{
    (void)func;
    if (argsNum != ArgsCount::NUM_2 ) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: the number of createPattern method parameter error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("createPattern method parameter error"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }

    ACE_FREE(component->patternPathValue_);
    ACE_FREE(component->patternRepeatTypeValue_);
    component->patternPathValue_ = MallocStringOf(args[ArgsIndex::IDX_0]);
    component->patternRepeatTypeValue_ = MallocStringOf(args[ArgsIndex::IDX_1]);
    if (component->patternPathValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: patternPath value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("patternPath value erro!"));
    }
    if (component->patternRepeatTypeValue_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: patternRepeatType value error!");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("patternRepeatType value erro!"));
    }
    if (IsFileExisted(component->patternPathValue_)) {
        component->paint_.CreatePattern(component->patternPathValue_,component->patternRepeatTypeValue_);
    } else {
        component->canvas_.Stroke(component->paint_);
    }

    return UNDEFINED;
}

jerry_value_t CanvasComponent::Fill(const jerry_value_t func,
                                      const jerry_value_t context,
                                      const jerry_value_t args[],
                                      const jerry_length_t argsNum)
{
    (void)func;
    (void)args;
    (void)argsNum;
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    component->canvas_.Fill(component->paint_);
    return UNDEFINED;
}


jerry_value_t CanvasComponent::DrawImage(const jerry_value_t func, const jerry_value_t context,
                                         const jerry_value_t args[], const jerry_length_t argsNum)
{
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    if (argsNum < ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: DrawImage arg error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("canvas_component: DrawImage arg error!"));
    }
    ImageModule* imageModule = nullptr;
    ImageComponent* imageCom = nullptr;
    char *imageName = nullptr;
    const char * src = nullptr;
    int16_t startX = 0;
    int16_t startY = 0;
    int16_t width = -1;
    int16_t height = -1;
    if(jerry_value_is_string(args[ArgsIndex::IDX_0])){// 参数是文件名
        imageName = MallocStringOf(args[ArgsIndex::IDX_0]);
        if (imageName == nullptr) {
            HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get imageName value failed");
            return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("get imageName value failed"));
        }
    } else if(jerry_value_is_object(args[ArgsIndex::IDX_0])){// 参数是从HTML获取到的对象
        void *nativePtr = nullptr;
        bool exist = jerry_get_object_native_pointer(args[ArgsIndex::IDX_0], &nativePtr, nullptr);
        imageModule = reinterpret_cast<ImageModule*>(nativePtr);//
        imageCom = reinterpret_cast<ImageComponent*>(nativePtr);
        if(imageCom){
            src = imageCom->GetSrc();
            if(src == nullptr){
                HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get imagePath value failed");
                return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("get imagePath value failed"));
            }
            imageName = (char*)malloc(strlen(src) + 1);
            strcpy_s(imageName, strlen(src) + 1, src);
        }else{// 参数是通过 new Image()的对象
            jerry_value_t src = jerryx_get_property_str(args[ArgsIndex::IDX_0],ImageModule::ATTR_SRC);
            char* srcVal = MallocStringOf(src);
            imageName = (char*)malloc(strlen(srcVal) + 1);
            strcpy_s(imageName, strlen(srcVal) + 1, srcVal);
            ACE_FREE(srcVal);
            jerry_value_t jWidth = jerryx_get_property_str(args[ArgsIndex::IDX_0],ImageModule::ATTR_WIDTH);
            jerry_value_t jHeight = jerryx_get_property_str(args[ArgsIndex::IDX_0],ImageModule::ATTR_HEIGHT);
            width = IntegerOf(jWidth);
            height = IntegerOf(jHeight);
        }
    } else{
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get imageName value failed");
        return jerry_create_error(JERRY_ERROR_TYPE, reinterpret_cast<const jerry_char_t *>("get imageName value failed"));
    }

    if (argsNum >= ArgsCount::NUM_2){
        startX = IntegerOf(args[ArgsIndex::IDX_1]);
    }
    if (argsNum >= ArgsCount::NUM_3){
        startY = IntegerOf(args[ArgsIndex::IDX_2]);
    }
    if (argsNum >= ArgsCount::NUM_4){
        width = IntegerOf(args[ArgsIndex::IDX_3]);
    }
    if (argsNum >= ArgsCount::NUM_5){
        height = IntegerOf(args[ArgsIndex::IDX_4]);
    }
    Point startLocat = {startX, startY};
    component->canvas_.DrawImage(startLocat, imageName, component->paint_, width, height);
    free(imageName);
    return UNDEFINED;
}

jerry_value_t CanvasComponent::SetLineDash(const jerry_value_t func, const jerry_value_t context, const jerry_value_t args[], const jerry_length_t argsNum)
{
    if (argsNum != ArgsCount::NUM_1) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: SetLineDash arg error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("canvas_component: DrawImage arg error!"));
    }

    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    jerry_value_t array = args[ArgsIndex::IDX_0];
    if(!jerry_value_is_array(array)){
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: SetLineDash arg error!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("canvas_component: DrawImage arg error!"));
    }
    uint32_t len = jerry_get_array_length(array);
    float *buff = new float[len];
    for (uint32_t i = 0; i < len; i++) {
        jerry_value_t val = jerry_get_property_by_index(array, i);
        float num = 0;
        if(jerry_value_is_number(val)){
            num = jerry_get_number_value(val);
        }
        else if(jerry_value_is_string(val)){
            char *value = MallocStringOf(val);
            num = atof(value);
            ACE_FREE(value);
        }else{
             HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: SetLineDash arg error!");
        }

        buff[i] = num;
        jerry_release_value(val);
    }

    component->paint_.SetLineDash(buff, len);
    delete[] buff;
    return UNDEFINED;
}

jerry_value_t CanvasComponent::GetLineDash(const jerry_value_t func, const jerry_value_t context, const jerry_value_t args[], const jerry_length_t argsNum)
{
    CanvasComponent *component = static_cast<CanvasComponent *>(ComponentUtils::GetComponentFromBindingObject(context));
    if (component == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get canvas component from js object failed!");
        return jerry_create_error(JERRY_ERROR_TYPE,
                                  reinterpret_cast<const jerry_char_t *>("get canvas component from js object failed"));
    }
    float* pArr = component->paint_.GetLineDash();
    uint32_t length = component->paint_.GetLineDashCount();
    jerry_release_value(component->dashArray_);
    component->dashArray_ = jerry_create_array(length);
    for (uint32_t i = 0; i < length; i++) {
        jerry_set_property_by_index(component->dashArray_ ,i , jerry_create_number(pArr[i]));
    }
    return component->dashArray_;

}

void CanvasComponent::GetSubFont(const char *font, const uint8_t index, char *&subFont) const
{
    if (font == nullptr || *font == '\0') {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: get font attribute failed");
        return;
    }

    if (strlen(font) >= UINT16_MAX) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: font size overflow.");
        return;
    }

    // skip space character at the head of string.
    while ((*font != '\0') && (*font == ' ')) {
        font++;
    }

    uint8_t currentIndex = 0;
    const char *currentPos = font;
    const char *endPos = font;
    while (*currentPos != '\0') {
        // find the sub font string
        if (currentIndex == index) {
            if (*endPos != ' ' && *endPos != '\0') {
                endPos++;
                continue;
            }
            uint16_t len = endPos - currentPos;
            uint16_t startIndex = currentPos - font;
            subFont = static_cast<char *>(ace_malloc(len + 1));
            if (subFont == nullptr) {
                HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: malloc buffer failed for subFont");
                return;
            }
            errno_t error = strncpy_s(subFont, len + 1, font + startIndex, len);
            if (error != 0) {
                HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: copy string failed");
                ace_free(subFont);
                subFont = nullptr;
                return;
            }
            subFont[len] = '\0';
            break;
        }
        // go forward to next sub font string.
        if (*(currentPos) == ' ' && *(currentPos + 1) != ' ') {
            currentIndex = currentIndex + 1;
            endPos = currentPos + 1;
        }
        currentPos++;
    }
}

bool CanvasComponent::FormatArcAngle(double sAngle,
                                     double eAngle,
                                     int16_t &startAngle,
                                     int16_t &endAngle,
                                     bool counterClockwise) const
{
    constexpr int16_t DEGREES_180 = 180;
    constexpr int16_t DEGREES_360 = 360;

    // calculate start-angle and end-angle degrees
    if (((DEGREES_180 * sAngle / UI_PI) > INT16_MAX) || ((DEGREES_180 * sAngle / UI_PI) < INT16_MIN) ||
        ((DEGREES_180 * eAngle / UI_PI) > INT16_MAX) || ((DEGREES_180 * eAngle / UI_PI) < INT16_MIN)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "canvas_component: startAngle or endAngle overflow.");
        return false;
    }

    startAngle = DEGREES_180 * sAngle / UI_PI;
    endAngle = DEGREES_180 * eAngle / UI_PI;

    if (!counterClockwise) {
        // reset end-angle degrees when (endAngle - startAngle) > 360
        if ((endAngle - startAngle) > DEGREES_360) {
            endAngle = startAngle + DEGREES_360;
        }
        // reset start-angle or end-angle degrees when startAngle > endAngle
        if (startAngle <= endAngle) {
            return true;
        }
        while (startAngle >= endAngle) {
            if ((endAngle + DEGREES_360) > INT16_MAX) {
                startAngle = startAngle - DEGREES_360;
                break;
            }
            endAngle = endAngle + DEGREES_360;
        }
    } else {
        // reset end-angle degrees when (endAngle - startAngle) > 360
        if ((startAngle - endAngle) > DEGREES_360) {
            endAngle = startAngle - DEGREES_360;
        }
        // reset start-angle or end-angle degrees when startAngle < endAngle
        if (startAngle >= endAngle) {
            return true;
        }
        while (startAngle <= endAngle) {
            if ((endAngle - DEGREES_360) < INT16_MIN) {
                startAngle = startAngle + DEGREES_360;
                break;
            }
            endAngle = endAngle - DEGREES_360;
        }
    }

    return true;
}

void CanvasComponent::RegisterAttributeFunc(jerry_value_t canvas2dContext,
                                            const char *attributeName,
                                            jerry_external_handler_t setterHandler,
                                            jerry_external_handler_t getterHandler)
{
    // register canvas js attribute setter property via the jerry_define_own_property method
    jerry_value_t propName = jerry_create_string(reinterpret_cast<const jerry_char_t *>(attributeName));
    jerry_property_descriptor_t desc;
    jerry_init_property_descriptor_fields(&desc);
    desc.is_set_defined = true;
    desc.setter = jerry_create_external_function(setterHandler);
    desc.is_get_defined = true;
    desc.getter = jerry_create_external_function(getterHandler);
    jerry_value_t returnValue = jerry_define_own_property(canvas2dContext, propName, &desc);
    jerry_free_property_descriptor_fields(&desc);
    ReleaseJerryValue(propName, returnValue, VA_ARG_END_FLAG);
}

void CanvasComponent::RegisterDrawMethodFunc(jerry_value_t canvas2dContext,
                                             const char *drawMethodName,
                                             jerry_external_handler_t handler)
{
    JerrySetFuncProperty(canvas2dContext, drawMethodName, handler);
}
} // namespace ACELite
} // namespace OHOS
#endif // FEATURE_COMPONENT_CANVAS
