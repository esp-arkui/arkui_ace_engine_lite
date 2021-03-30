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

#include "async_task_manager.h"
#include "ace_log.h"
#include "fatal_handler.h"
#include "ace_lock.h"

namespace OHOS {
namespace ACELite {
AsyncTaskManager::AsyncTaskManager()
    : head_(nullptr),
      tail_(nullptr),
      uniqueTaskID_(0),
      front_(true)
{
}

AsyncTaskManager::~AsyncTaskManager()
{
    while (head_ != nullptr) {
        AsyncTask *task = head_;
        head_ = head_->next;
        delete task;
        task = nullptr;
    }
    tail_ = nullptr;
}

AsyncTaskManager &AsyncTaskManager::GetInstance()
{
    static AsyncTaskManager instance;
    return instance;
}

void AsyncTaskManager::Init()
{
    Task::Init();
}

void AsyncTaskManager::Callback()
{
    if (!front_) {
        return;
    }

    while (head_ != nullptr) {
        AsyncTask *task = head_;
        task->handler(task->data);
        if (head_ == tail_) {
            tail_ = nullptr;
        }
        head_ = head_->next;
        delete task;
        task = nullptr;
    }
}

uint16_t AsyncTaskManager::Dispatch(AsyncTaskHandler handler, void *data)
{
    if (handler == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AsyncTaskManager::Dispatch failed: handler is null.");
        return DISPATCH_FAILURE;
    }
    if (FatalHandler::GetInstance().IsFatalErrorHitted()) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AsyncTaskManager::Dispatch failed: Fatal error is hitted.");
        return DISPATCH_FAILURE;
    }
    AutoLockGuard autoLock(lock_);
    auto *task = new AsyncTask();
    if (task == nullptr) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AsyncTaskManager::Dispatch failed: out of memory.");
        return DISPATCH_FAILURE;
    }
    task->handler = handler;
    task->data = data;
    task->id = (++uniqueTaskID_);
    task->next = nullptr;
    if (head_ == nullptr) {
        head_ = task;
        tail_ = task;
    } else {
        tail_->next = task;
        tail_ = task;
    }
    return uniqueTaskID_;
}

void AsyncTaskManager::Cancel(uint16_t taskID)
{
    if (DISPATCH_FAILURE == taskID) {
        HILOG_ERROR(HILOG_MODULE_ACE, "AsyncTaskManager::Cancel failed: invalid task ID.");
        return;
    }
    AutoLockGuard autoLock(lock_);
    AsyncTask *node = head_;
    AsyncTask *prev = nullptr;
    while (node != nullptr) {
        if (node->id == taskID) {
            if (prev == nullptr) {
                head_ = head_->next;
            } else {
                prev->next = node->next;
                if (node == tail_) {
                    tail_ = prev;
                }
            }
            delete node;
            node = nullptr;
            break;
        }
        prev = node;
        node = node->next;
    }
}

void AsyncTaskManager::SetFront(bool front)
{
    front_ = front;
}
} // namespace ACELite
} // namespace OHOS
