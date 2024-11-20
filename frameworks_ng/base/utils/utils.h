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

#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_BASE_UTILS_UTILS_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_BASE_UTILS_UTILS_H

namespace OHOS{
namespace ACELite {
inline bool GreatNotEqual(double left, double right)
{
    constexpr double epsilon = 0.001f;
    return (left - right) > epsilon;
}

inline bool GreatNotEqualCustomPrecision(double left, double right, double epsilon = 0.000001f)
{
    return (left - right) > epsilon;
}

inline bool GreatOrEqual(double left, double right)
{
    constexpr double epsilon = -0.001f;
    return (left - right) > epsilon;
}

inline bool NonNegative(double value)
{
    return GreatOrEqual(value, 0);
}

inline bool LessOrEqual(double left, double right)
{
    constexpr double epsilon = 0.001f;
    return (left - right) < epsilon;
}

inline bool NonPositive(double value)
{
    return LessOrEqual(value, 0);
}


}
}

#endif