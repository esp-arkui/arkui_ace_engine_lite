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

#include "stylemgr_media_query_tdd_test.h"
#include "js_debugger_config.h"
#include "stylemgr/app_style_manager.h"
#include "stylemgr/app_style_sheet.h"
#include <cstdio>

namespace OHOS {
namespace ACELite {
void StyleMgrMediaQueryTddTest::SetUp()
{
    Debugger::GetInstance().SetupJSContext();
    jerry_init(JERRY_INIT_EMPTY);
}

void StyleMgrMediaQueryTddTest::TearDown()
{
    jerry_cleanup();
    Debugger::GetInstance().ReleaseJSContext();
}

void StyleMgrMediaQueryTddTest::RunTests() {}

/**
 * @tc.name: StyleMgrMediaQueryCSS001
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: SR000GCSKI
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS001, TestSize.Level0)
{
}

/**
 * @tc.name: StyleMgrMediaQueryCSS002
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKJ
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS002, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS003
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKK
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS003, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS004
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKL
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS004, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS005
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKM
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS005, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS006
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKN
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS006, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS007
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKN
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS007, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS008
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKN
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS008, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS009
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKN
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS009, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS010
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKN
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS010, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS011
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKN
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS011, TestSize.Level0) {}

/**
 * @tc.name: StyleMgrMediaQueryCSS012
 * @tc.desc: Verify the style sheet with media query block initialization
 * @tc.require: AR000GCSKN
 */
HWTEST_F(StyleMgrMediaQueryTddTest, StyleMgrMediaQueryCSS012, TestSize.Level0) {}
} // namespace ACELite
} // namespace OHOS
