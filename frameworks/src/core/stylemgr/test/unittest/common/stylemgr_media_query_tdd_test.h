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
#ifndef ACELITE_STYLE_MANAGER_MEDIA_QUERY_TDD_TEST_H
#define ACELITE_STYLE_MANAGER_MEDIA_QUERY_TDD_TEST_H

#ifdef TDD_ASSERTIONS
#include <climits>
#include <gtest/gtest.h>
#else
#include <typeinfo.h>
#endif

#include "acelite_config.h"

namespace OHOS {
namespace ACELite {
#ifdef TDD_ASSERTIONS
using namespace std;
using namespace testing::ext;
class StyleMgrMediaQueryTddTest : public testing::Test {
#else
class StyleMgrMediaQueryTddTest {
#endif
public:
    StyleMgrMediaQueryTddTest() = default;
    ~StyleMgrMediaQueryTddTest() = default;
    void SetUp();
    void TearDown();

    void StyleMgrMediaQueryCSS001();
    void StyleMgrMediaQueryCSS002();
    void StyleMgrMediaQueryCSS003();
    void StyleMgrMediaQueryCSS004();
    void StyleMgrMediaQueryCSS005();
    void StyleMgrMediaQueryCSS006();
    void StyleMgrMediaQueryCSS007();
    void StyleMgrMediaQueryCSS008();
    void StyleMgrMediaQueryCSS009();
    void StyleMgrMediaQueryCSS010();
    void StyleMgrMediaQueryCSS011();
    void StyleMgrMediaQueryCSS012();
    void RunTests();
};
} // namespace ACELite
} // namespace OHOS
#endif // ACELITE_STYLE_MANAGER_MEDIA_QUERY_TDD_TEST_H
