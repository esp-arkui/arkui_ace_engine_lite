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

#include "list_adapter.h"

#include <stdlib.h>

#include "ace_log.h"
#include "ace_mem_base.h"
#include "component_utils.h"
#include "directive/descriptor_utils.h"
#include "fatal_handler.h"
#include "securec.h"
#include "js_profiler.h"

namespace OHOS {
namespace ACELite {
ListAdapter::ListAdapter()
    : listItems_(nullptr),
      headNode_(nullptr),
      tailNode_(nullptr),
      itemsCount_(0),
      listItemsCount_(0),
      uiListContentParam_()
{
}

ListAdapter::~ListAdapter()
{
    if (listItems_) {
        delete[] listItems_;
        listItems_ = nullptr;
    }

    ViewNativePair *currentNode = headNode_;
    ViewNativePair *nextNode = nullptr;

    if (currentNode == nullptr) {
        HILOG_DEBUG(HILOG_MODULE_ACE, "the viewNativePair linked list is null");
    }
    // delete the node info
    while (currentNode != nullptr) {
        nextNode = currentNode->next;
        // only let list component release its children when the whole application
        // is not in fatal error handling process, as FatalHandler will do the recycle
        if (!FatalHandler::GetInstance().IsFatalErrorHandling()) {
            delete currentNode;
        }
        currentNode = nextNode;
    }
    // delete nativeElement in viewNativePair link list, then free viewNativePair link list.
    headNode_ = nullptr;
    tailNode_ = nullptr;

    itemsCount_ = 0;
    listItemsCount_ = 0;
}

ViewNativePair::~ViewNativePair()
{
    // release component render list
    renderComponentList.Clear();
    if (rootView == nullptr) {
        return;
    }
    UIView::ViewExtraMsg *msg = rootView->GetExtraMsg();
    if (msg == nullptr) {
        return;
    }
    JSValue *element = reinterpret_cast<JSValue *>(msg->elementPtr);
    if (element == nullptr) {
        return;
    }
    DescriptorUtils::ReleaseDescriptorOrElement(*element);
}

bool ListAdapter::Initialize(const JSValue descriptors)
{
    // check the children can be initialized.
    if (jerry_value_is_undefined(descriptors) || !jerry_value_is_array(descriptors)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: initialize children failed!");
        return false;
    }

    int16_t size = JSArray::Length(descriptors);
    if ((size == 0) || (size >= INT16_MAX)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: descriptors size invalid.");
        return false;
    }
    listItems_ = new ListItemValue[size];
    // initialize the listItems_ array.
    if (listItems_ == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: listItems_ array failed to allocate memory!");
        return false;
    }

    // generate the listItems_ array and return result.
    return GenerateListItems(descriptors, size);
}

bool ListAdapter::GenerateListItems(const JSValue descriptors, int16_t size)
{
    bool result = false;
    int16_t listItemsIndex = 0;
    int16_t startIndex = 0;

    for (int16_t index = 0; index < size; ++index) {
        JSValue descriptorOrElement = JSArray::Get(descriptors, index);
        if (JSUndefined::Is(descriptorOrElement)) {
            HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: get descriptorOrElement from descriptors failed!");
            continue;
        }

        listItems_[listItemsIndex].descriptorOrElement = descriptorOrElement;
        listItems_[listItemsIndex].startIndex = startIndex;

        // if it is a for type list-item
        if (DescriptorUtils::IsForDescriptor(descriptorOrElement)) {
            bool success = AddForDescriptorToList(descriptorOrElement, listItemsIndex);
            if (!success) {
                JSRelease(descriptorOrElement);
                continue;
            }
        } else { // if it is a if or common type list-item
            if (DescriptorUtils::IsIfDescriptor(descriptorOrElement)) {
                bool isShown = DescriptorUtils::IsIfDescriptorShown(descriptorOrElement);
                if (!isShown) {
                    JSRelease(descriptorOrElement);
                    result = true;
                    continue;
                }
            }
            listItems_[listItemsIndex].getterRetList = UNDEFINED;
            listItems_[listItemsIndex].itemsCount = 1;
        }

        // sum of all descriptors list-items.
        itemsCount_ = itemsCount_ + listItems_[listItemsIndex].itemsCount;
        // sum of all descriptors.
        listItemsCount_ = listItemsCount_ + 1;
        startIndex = startIndex + listItems_[listItemsIndex].itemsCount;
        listItemsIndex++;

        JSRelease(descriptorOrElement);
        result = true;
    }
    return result;
}

bool ListAdapter::AddForDescriptorToList(JSValue descriptorOrElement, int16_t listItemsIndex) const
{
    JSValue getterPropValue = jerryx_get_property_str(descriptorOrElement, DESCRIPTOR_ATTR_GETTER);
    if (!jerry_value_is_function(getterPropValue)) {
        ReleaseJerryValue(getterPropValue, VA_ARG_END_FLAG);
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Getter argument is not a function.");
        return false;
    }

    JSValue getterRetList = CallJSFunctionOnRoot(getterPropValue, nullptr, 0);
    // check whether result is an array
    if (!jerry_value_is_array(getterRetList)) {
        ReleaseJerryValue(getterPropValue, getterRetList, VA_ARG_END_FLAG);
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: fetch getter array error.");
        return false;
    }

    // save getterRetList.
    listItems_[listItemsIndex].getterRetList = getterRetList;
    // save getterRetList length.(the length is the count of current descriptor list-item)
    listItems_[listItemsIndex].itemsCount = jerry_get_array_length(getterRetList);
    ReleaseJerryValue(getterPropValue, getterRetList, VA_ARG_END_FLAG);
    return true;
}

// find listItemsIndex according the itemIndex
int16_t ListAdapter::CalculateItemIndex(int16_t itemIndex) const
{
    if (listItems_ == nullptr) {
        return FAILED;
    }

    for (int16_t listItemsIndex = 0; listItemsIndex < listItemsCount_; listItemsIndex++) {
        if (itemIndex >= listItems_[listItemsIndex].startIndex &&
            itemIndex <= (listItems_[listItemsIndex].startIndex + listItems_[listItemsIndex].itemsCount - 1) &&
            itemIndex < itemsCount_) {
            // found.
            return listItemsIndex;
        }
    }
    // not found.
    return FAILED;
}

UIView *ListAdapter::GetView(UIView *inView, int16_t index)
{
    if (index < 0) {
        return nullptr;
    }
    // 1. get UIView according to index which will show in list.
    int16_t listItemsIndex = CalculateItemIndex(index);
    if (listItemsIndex < 0) {
        return nullptr;
    }
    bool isFor = DescriptorUtils::IsForDescriptor(listItems_[listItemsIndex].descriptorOrElement);
    // if render the for type element, try to reuse the native element
    // if the current item is not rendered by for, get the target render element
    if (inView != nullptr && isFor) {
        return ChangeForView(inView, listItemsIndex, index);
    }
    JSValue element = UNDEFINED;
    JSValue descriptorOrElement = listItems_[listItemsIndex].descriptorOrElement;

    if (isFor) {
        // inView is nullptr, create the element tree and record the created sequence
        return CreateForView(listItemsIndex, index);
    } else if(DescriptorUtils::IsIfDescriptor(descriptorOrElement)) {
        element = DescriptorUtils::GetDescriptorRendered(descriptorOrElement);
        if (IS_UNDEFINED(element)) {
            element = DescriptorUtils::RenderIfDescriptor(descriptorOrElement);
        }
    } else {
        element = descriptorOrElement;
    }
    BuildItemViewTree(element);
    if (jerry_value_is_undefined(element)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Failed to get element.");
        return nullptr;
    }
    // get rootview from nativeElement
    UIView *newView = ComponentUtils::GetViewFromBindingObject(element);
    if (newView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Failed to get view from js object.");
        jerry_release_value(element);
        return nullptr;
    }
    return newView;
}

UIView *ListAdapter::CreateForView(int16_t listItemIndex, int16_t index)
{
    ViewNativePair *pair = new ViewNativePair();
    if (pair == nullptr) {
        return nullptr;
    }
    // add the _createList_ attribute to viewModel to record the created sequence
    JSValue viewModel = JSGlobal::Get(ATTR_ROOT);
    JSValue renderObj = JSObject::Create();
    JSObject::SetNativePointer(renderObj, &pair->renderComponentList);
    JSObject::Set(viewModel, "_createList_", renderObj);
    // add _descriptor to check the render item has if or not
    JSObject::SetBoolean(viewModel, "_descriptor", false);
    JSValue element = GetElementFromFor(listItemIndex, index);
    JSObject::Del(viewModel, "_createList_");
    bool isAddToList = !JSObject::GetBoolean(viewModel, "_descriptor");
    JSObject::Del(viewModel, "_descriptor");
    JSObject::DelNativePointer(renderObj);
    ReleaseJerryValue(renderObj, viewModel, VA_ARG_END_FLAG);
    if (jerry_value_is_undefined(element)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Failed to get element.");
        return nullptr;
    }
    UIView *newView = ComponentUtils::GetViewFromBindingObject(element);
    if (newView == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Failed to get view from js object.");
        jerry_release_value(element);
        return nullptr;
    }
    BuildItemViewTree(element);
    // add the item component node the list
    pair->rootView = newView;
    pair->listItemIndex = listItemIndex;
    pair->hasDescriptor = isAddToList;
    if (headNode_ == nullptr) {
        headNode_ = pair;
        tailNode_ = headNode_;
    } else {
        tailNode_->next = pair;
        tailNode_ = pair;
    }
    return newView;
}

UIView *ListAdapter::ChangeForView(UIView *inView, int16_t listItemIndex, int16_t index) const
{
    // find the target element by inView
    ViewNativePair *current = headNode_;
    while (current != nullptr) {
        if (current->rootView == inView) {
            break;
        }
        current = current->next;
    }
    if (current == nullptr || (current->rootView != inView)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "find target ui view failed");
        return nullptr;
    }
    // if the item is not rendered by if command and the listIndex is the same with last rendered listItem,
    // reuse the native element
    if (!current->hasDescriptor && (listItemIndex == current->listItemIndex)) {
        return ReuseNativeView(current, listItemIndex, index);
    }
    // cann't reuse the native view, get the root element of the target list item, then release the native resource
    UIView::ViewExtraMsg *msg = current->rootView->GetExtraMsg();
    if (msg == nullptr) {
        return nullptr;
    }
    JSValue *element = reinterpret_cast<JSValue *>(msg->elementPtr);
    if (element == nullptr) {
        return nullptr;
    }
    DescriptorUtils::ReleaseDescriptorOrElement(*element);
    JSValue viewModel = JSGlobal::Get(ATTR_ROOT);
    // render the new list item
    JSValue renderObj = JSObject::Create();
    // delete the last rendered component list
    current->renderComponentList.Clear();
    // set the new listItem index in list record node
    current->listItemIndex = listItemIndex;
    JSObject::SetNativePointer(renderObj, &current->renderComponentList);
    JSObject::Set(viewModel, "_createList_", renderObj);
    JSObject::Set(viewModel, "_isDescriptor", false);
    JSValue newEle = GetElementFromFor(listItemIndex, index);
    JSObject::Del(viewModel, "_createList_");
    JSObject::Del(viewModel, "_isDescriptor");
    JSObject::DelNativePointer(renderObj);
    ReleaseJerryValue(viewModel, renderObj, VA_ARG_END_FLAG);
    BuildItemViewTree(newEle);
    current->rootView = ComponentUtils::GetViewFromBindingObject(newEle);
    return current->rootView;
}

UIView *ListAdapter::ReuseNativeView(ViewNativePair *current, int16_t listItemIndex, int16_t index) const
{
    ListNode<Component *> *currentRender = current->renderComponentList.Head();
    if (currentRender == nullptr) {
        return nullptr;
    }
    JSValue viewModel = JSGlobal::Get(ATTR_ROOT);
    // set the reused component list to _renderList_ attribute in viewModel
    JSValue renderObj = JSObject::Create();
    JSObject::SetNativePointer(renderObj, currentRender);
    JSObject::Set(viewModel, "_renderList_", renderObj);
    JSValue element = listItems_[listItemIndex].descriptorOrElement;
    JSValue getterRetList = listItems_[listItemIndex].getterRetList;
    int16_t startIndex = listItems_[listItemIndex].startIndex;
    // if it is a for or for+if type list-item, we need create view dynamically.
    // get render argument
    JSValue item = jerry_get_property_by_index(getterRetList, index - startIndex);
    if (jerry_value_is_undefined(item)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Get item from getterRetList failed.");
        ReleaseJerryValue(renderObj, viewModel, VA_ARG_END_FLAG);
        return nullptr;
    }
    JSValue itemIdx = jerry_create_number(index - startIndex);
    const int8_t argsLen = 2;
    JSValue args[argsLen] = {item, itemIdx};
    // get render function
    JSValue renderPropValue = jerryx_get_property_str(element, DESCRIPTOR_ATTR_RENDER);
    if (!jerry_value_is_function(renderPropValue)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Get View failed, render argument is not a function.");
        ReleaseJerryValue(item, itemIdx, renderPropValue, viewModel, renderObj, VA_ARG_END_FLAG);
        return nullptr;
    }
    // excute render function, get nativeElement
    JSValue nativeElement = CallJSFunction(renderPropValue, UNDEFINED, args, argsLen);
    // if it is a for+if type list-item, here will ignore if attribute
    if (DescriptorUtils::IsIfDescriptor(nativeElement)) {
        element = DescriptorUtils::GetDescriptorRendered(nativeElement);
        if (IS_UNDEFINED(element)) {
            element = DescriptorUtils::RenderIfDescriptor(nativeElement);
        }
        ReleaseJerryValue(nativeElement, VA_ARG_END_FLAG);
        HILOG_ERROR(HILOG_MODULE_ACE, "List_adapter: list-item not support setting if and for attribute at once.");
    } else { // if it is a for type list-item
        element = nativeElement;
    }
    JSObject::Del(viewModel, "_renderList_");
    JSObject::DelNativePointer(renderObj);
    ReleaseJerryValue(item, itemIdx, renderPropValue, viewModel, renderObj, VA_ARG_END_FLAG);
    return current->rootView;
}

JSValue ListAdapter::GetElementFromFor(int16_t listItemsIndex, int16_t index) const
{
    JSValue element = listItems_[listItemsIndex].descriptorOrElement;
    JSValue getterRetList = listItems_[listItemsIndex].getterRetList;
    int16_t startIndex = listItems_[listItemsIndex].startIndex;
    // if it is a for or for+if type list-item, we need create view dynamically.
    // get render argument
    JSValue item = jerry_get_property_by_index(getterRetList, index - startIndex);
    if (jerry_value_is_undefined(item)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Get item from getterRetList failed.");
        return UNDEFINED;
    }
    JSValue itemIdx = jerry_create_number(index - startIndex);
    const int8_t argsLen = 2;
    JSValue args[argsLen] = {item, itemIdx};
    // get render function
    JSValue renderPropValue = jerryx_get_property_str(element, DESCRIPTOR_ATTR_RENDER);
    if (!jerry_value_is_function(renderPropValue)) {
        HILOG_ERROR(HILOG_MODULE_ACE, "List adapter: Get View failed, render argument is not a function.");
        ReleaseJerryValue(item, itemIdx, renderPropValue, VA_ARG_END_FLAG);
        return UNDEFINED;
    }
    // excute render function, get nativeElement
    JSValue nativeElement = CallJSFunction(renderPropValue, UNDEFINED, args, argsLen);
    if (jerry_value_is_undefined(nativeElement)) {
        ReleaseJerryValue(item, itemIdx, renderPropValue, nativeElement, VA_ARG_END_FLAG);
        return UNDEFINED;
    }
    // if it is a for+if type list-item, here will ignore if attribute
    if (DescriptorUtils::IsIfDescriptor(nativeElement)) {
        element = DescriptorUtils::GetDescriptorRendered(nativeElement);
        if (IS_UNDEFINED(element)) {
            element = DescriptorUtils::RenderIfDescriptor(nativeElement);
        }
        ReleaseJerryValue(nativeElement, VA_ARG_END_FLAG);
        HILOG_ERROR(HILOG_MODULE_ACE, "List_adapter: list-item not support setting if and for attribute at once.");
    } else { // if it is a for type list-item
        element = nativeElement;
    }
    ReleaseJerryValue(item, itemIdx, renderPropValue, VA_ARG_END_FLAG);
    return element;
}

void ListAdapter::BuildItemViewTree(const JSValue element) const
{
    Component *component = ComponentUtils::GetComponentFromBindingObject(element);
    if (component == nullptr) {
        return;
    }
    ConstrainedParameter parentParam = uiListContentParam_;
    if (direction_ == UIList::VERTICAL) {
        if (component->GetDimension(K_WIDTH).type == DimensionType::TYPE_UNKNOWN) {
            component->SetWidth(uiListContentParam_.maxWidth);
        }
    } else {
        if (component->GetDimension(K_HEIGHT).type == DimensionType::TYPE_UNKNOWN) {
            component->SetHeight(uiListContentParam_.maxHeight);
        }
    }
    Component::BuildViewTree(component, nullptr, parentParam);
    component->OnViewAttached();
}

void ListAdapter::CleanUp()
{
    itemsCount_ = 0;
    listItemsCount_ = 0;

    if (listItems_ != nullptr) {
        delete[] listItems_;
        listItems_ = nullptr;
    }
}

void ListAdapter::UpdateContentAlignParam(ConstrainedParameter param)
{
    uiListContentParam_ = param;
}
} // namespace ACELite
} // namespace OHOS
