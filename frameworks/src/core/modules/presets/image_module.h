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

#ifndef OHOS_ACELITE_IMAGE_MODEL_H
#define OHOS_ACELITE_IMAGE_MODEL_H

#include "acelite_config.h"
#include "image_component.h"
#include "gfx_utils/list.h"
#include "js_fwk_common.h"

//#include "draw/draw_utils.h"
namespace OHOS {
namespace ACELite {
class ImageModule final :public MemoryHeap {//public ImageComponent{//MemoryHeap {
public:

    const char*  GetSrc(){
        return src_;
    }

    int16_t GetWidth(){
        return width_;
    }

    int16_t GetHeight(){
        return height_;
    }

    ACE_DISALLOW_COPY(ImageModule);
    /**
     * @brief register Image object
     */
    static void Init(jerry_value_t intlHandle);

    static void RegisterAttributeFunc(jerry_value_t canvas2dContext,
                                                const char *attributeName,
                                                jerry_external_handler_t setterHandler,
                                                jerry_external_handler_t getterHandler);
    /**
     * @brief delete the date format object
     * @param the pointer need to be delete
     */
    static void DeleteImage(void *nativePointer);

    static void OnCallBack(const jerry_value_t context,const ImageModule *imageModule,bool isSucess,const char* msg);
    // the handle to release the native value when the js value number format object is not needed.
    static constexpr jerry_object_native_info_t gcCallback = {.free_cb = DeleteImage};
    static const char * const ATTR_ONLOAD;
    static const char * const ATTR_ONERROR;
    static const char * const ATTR_SRC;
    static const char * const ATTR_WIDTH;
    static const char * const ATTR_HEIGHT;
    static const char * const CLASS_NAME;
private:
    ImageModule() :
        src_(nullptr),
        width_(-1),
        height_(-1),
        onLoadFunc_(UNDEFINED),
        onErrorFunc_(UNDEFINED),
        jerrySrc_(UNDEFINED){}

    ~ImageModule()
    {
        ACE_FREE(src_);
        jerry_release_value(onLoadFunc_);
        jerry_release_value(onErrorFunc_);
        jerry_release_value(jerrySrc_);
    }

    static jerry_value_t CreateImage(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnLoadSetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnLoadGetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnErrorSetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnErrorGetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnSrcSetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnSrcGetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnHeightSetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnHeightGetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnWidthSetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);
    static jerry_value_t OnWidthGetter(const jerry_value_t func,
                                const jerry_value_t context,
                                const jerry_value_t args[],
                                const jerry_length_t argsNum);

private:
    char* src_;
    int16_t width_;
    int16_t height_;
    jerry_value_t onLoadFunc_;
    jerry_value_t onErrorFunc_;
    jerry_value_t jerrySrc_;

};
}
}

#endif // NUMBER_FORMAT_MODEL_H
