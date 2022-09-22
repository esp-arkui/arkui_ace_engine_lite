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

#include "lazy_load_manager.h"
#include "ace_log.h"
#include "component_utils.h"
#include "descriptor_utils.h"
#include "fatal_handler.h"
#include "lazy_load_watcher.h"
#include "js_app_context.h"

namespace OHOS {
namespace ACELite {
LazyLoadManager::LazyLoadManager() : state_(LazyLoadState::INIT)
{
    ListNode<LazyLoadWatcher *> *node = lazyWatchersList_.Begin();
    node->data_ = nullptr;
}

LazyLoadManager::~LazyLoadManager()
{
    ResetWatchers();
}

void LazyLoadManager::ResetWatchers()
{
    ListNode<LazyLoadWatcher *> *node = lazyWatchersList_.Begin();
    while (node != lazyWatchersList_.End()) {
        if (node->data_ != nullptr) {
            delete node->data_;
            node->data_ = nullptr;
        }
        node = node->next_;
    }
    lazyWatchersList_.Clear();
    state_ = LazyLoadState::INIT;
}

void LazyLoadManager::RenderLazyLoadWatcher()
{
    // copy all nodes to temp list, as the render process may add/remove nodes
    List<LazyLoadWatcher *> tempList;
    ListNode<LazyLoadWatcher *> *node = lazyWatchersList_.Begin();
    while (node != lazyWatchersList_.End()) {
        if (node->data_ != nullptr) {
            tempList.PushBack(node->data_);
        }
        node = node->next_;
    }
    lazyWatchersList_.Clear();

    // handle all lazy watcher from the temp list
    node = tempList.Begin();
    while (node != tempList.End()) {
        if (node->data_ != nullptr) {
            // handle it
            RenderSingleLazyWatcher(*(node->data_));
            delete node->data_;
            node->data_ = nullptr;
        }
        node = node->next_;
    }
    tempList.Clear();

    // if new watcher lazy request added in list, do not mark the state as done
    if (lazyWatchersList_.Size() == 0) {
        state_ = LazyLoadState::DONE;
    }
    HILOG_DEBUG(HILOG_MODULE_ACE, "lazy watcher pending count %d",
                JsAppContext::GetInstance()->GetRemainingLazyWatcherCount());
    HILOG_DEBUG(HILOG_MODULE_ACE, "lazy watcher list len %d", lazyWatchersList_.Size());
}

void LazyLoadManager::RenderSingleLazyDescriptor(const LazyLoadWatcher &watcher) const
{
    Component *parent = watcher.GetParentComponent();
    Component *currentComponent = watcher.GetCurrentComponent();
    if (!FatalHandler::GetInstance().IsComponentValid(parent) ||
        !FatalHandler::GetInstance().IsComponentValid(currentComponent)) {
        return;
    }
    jerry_value_t descriptor = watcher.GetDescriptor();
    if (IS_UNDEFINED(descriptor)) {
        return;
    }

    bool updateNeeded = true;
    if (DescriptorUtils::IsIfDescriptor(descriptor)) {
        // only update if the value changed for if descriptor case
        updateNeeded = (watcher.GetDescriptorIfValue() != DescriptorUtils::IsIfDescriptorShown(descriptor));
    }
    if (updateNeeded) {
        parent->HandleChildrenChange(descriptor);
    }

    currentComponent->CreateDirectiveWatcher(descriptor);
}

void LazyLoadManager::RenderSingleLazyWatcher(const LazyLoadWatcher &watcher) const
{
    if (watcher.IsDescriptor()) {
        RenderSingleLazyDescriptor(watcher);
        return;
    }
    jerry_value_t attrName = watcher.GetAttrName();
    jerry_value_t attrGetter = watcher.GetAttrGetter();
    uint16_t attrKeyID = watcher.GetKeyId();
    Component *component = watcher.GetCurrentComponent();
    if (!FatalHandler::GetInstance().IsComponentValid(component)) {
        return;
    }
    jerry_value_t latestValue = component->AddWatcherItem(attrName, attrGetter, true);
    if (attrKeyID == K_UNKNOWN) {
        // try to parse from attr name directly
        attrKeyID = ParseKeyIdFromJSString(attrName);
    }

    if ((!IS_UNDEFINED(latestValue)) && (attrKeyID != K_UNKNOWN)) {
        // need to update the view with the latest value, in case the value is already changed
        if (component->UpdateView(attrKeyID, latestValue)) {
            component->Invalidate();
        }
    }
    // the new value has been calculated out by ParseExpression, need to be released
    jerry_release_value(latestValue);
}

void LazyLoadManager::AddLazyLoadWatcher(Component *parent, Component *currentComponent, jerry_value_t descroptor)
{
    if (currentComponent == nullptr || descroptor == UNDEFINED) {
        return;
    }

    LazyLoadWatcher *watcher = new LazyLoadWatcher(parent, currentComponent, descroptor);
    if (watcher == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create watcher error");
        return;
    }
    lazyWatchersList_.PushBack(watcher);
    // The state must be ready if any watcher lazy loading request was added, otherwise, in some cases,
    // the js_ability may not be able to know there are watchers need to be loaded.
    state_ = LazyLoadState::READY;
}

void LazyLoadManager::AddLazyLoadWatcher(Component *component,
                                         jerry_value_t attrName,
                                         jerry_value_t getter)
{
    // pass key ID as UNKNOWN, and will be calculated out from attrName when using
    AddLazyLoadWatcher(component, attrName, getter, K_UNKNOWN);
}

void LazyLoadManager::AddLazyLoadWatcher(Component *component,
                                         jerry_value_t attrName,
                                         jerry_value_t getter,
                                         uint16_t keyId)
{
    if (component == nullptr || attrName == UNDEFINED || getter == UNDEFINED) {
        return;
    }

    LazyLoadWatcher *watcher = new LazyLoadWatcher(component, attrName, getter, keyId);
    if (watcher == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "create watcher errpr");
        return;
    }
    lazyWatchersList_.PushBack(watcher);
    // The state must be ready if any watcher lazy loading request was added, otherwise, in some cases,
    // the js_ability may not be able to know there are watchers need to be loaded.
    state_ = LazyLoadState::READY;
}

void LazyLoadManager::RemoveLazyWatcher(Component *component)
{
    if (lazyWatchersList_.IsEmpty() || component == nullptr) {
        return;
    }

    ListNode<LazyLoadWatcher *> *node = lazyWatchersList_.Begin();
    while (node != lazyWatchersList_.End()) {
        if (node->data_ == nullptr) {
            node = node->next_;
            continue;
        }
        if (node->data_->GetCurrentComponent() == component) {
            // found, remove the node
            delete node->data_;
            node->data_ = nullptr;
            node = lazyWatchersList_.Remove(node);
            continue;
        }
        node = node->next_;
    }
}
} // namespace ACELite
} // namespace OHOS
