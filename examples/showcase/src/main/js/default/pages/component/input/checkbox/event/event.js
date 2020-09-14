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
import { goPage, routePage } from "../../../../../common/js/general";
export default {
    data: {
        name: "点击或长按",
        checked: "触发change",
        show: true
    },
    clickEvent() {
        this.name = "点击事件触发";
    },
    longpressEvent() {
        this.name = "长按事件触发";
    },
    swipeEvent(e) {
        this.name = "swipe方向：" + e.direction;
    },
    changeEvent(e) {
        this.checked = "change触发";
    },
    ...goPage("pages/component/input/checkbox/index/index")
};
