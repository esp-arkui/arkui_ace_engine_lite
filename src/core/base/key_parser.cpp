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

#include "key_parser.h"
#include "acelite_config.h"
#include "js_config.h"
#include "keys.h"
#include <string.h>

namespace OHOS {
namespace ACELite {
#ifdef KEYWORD
#undef KEYWORD
#endif // KEYWORD

// Replace the struct keys.h "KEYWORD" sector for init
#if defined(ENABLE_KEY)
#define KEYWORD(enumkey, keystr) {#keystr, K_##enumkey, static_cast<uint8_t>(strlen(#enumkey))},
#else // ENABLE_KEY
#define KEYWORD(enumkey, keystr) {K_##enumkey, static_cast<uint8_t>(strlen(#enumkey))},
#endif // ENABLE_KEY

static const struct {
#if defined(ENABLE_KEY)
    const char *const key;
#endif
    const uint16_t ID;
    const uint8_t LENGTH;
} G_KEYWORD_INFO[KEYWORDS_MAX] = {
#if defined(ENABLE_KEY)
    {"UNKNOWN", K_UNKNOWN, static_cast<uint8_t>(strlen("UNKNOWN"))},
#else  // ENABLE_KEY
    {K_UNKNOWN, static_cast<uint8_t>(strlen("UNKNOWN"))},
#endif // ENABLE_KEY

#ifdef OHOS_ACELITE_KEYS_H
// include the keys.h again to redefine the "KEYWORD"
#undef OHOS_ACELITE_KEYS_H
#include "keys.h"
#endif // OHOS_ACELITE_KEYS_H
};
#undef KEYWORD

static const char js_keys[] =
#define KEYWORD(name, str) #str "\0"
#include "keys.h"
#undef KEYWORD
    ;

uint16_t KeyParser::ParseKeyId(const char *s, const size_t len)
{
    if (s == nullptr || len >= UINT16_MAX || len == 0) {
        return K_UNKNOWN;
    }

    int len;
    const char *p = js_keys;

    for (uint16_t i = 1; i < KEYWORDS_MAX; i++) {
        len = strlen(p);
        if (!strcmp(key, p)) {
            return i;
        }
        p = p + len + 1;
    }

    return K_UNKNOWN;
}

uint16_t KeyParser::ParseKeyId(const char *const s)
{
    if (s == nullptr) {
        return K_UNKNOWN;
    }

    size_t len = strlen(s);
    if (len >= UINT16_MAX) {
        return K_UNKNOWN;
    }
    return ParseKeyId(s, len);
}

bool KeyParser::IsKeyValid(uint16_t id)
{
    return ((id > K_UNKNOWN) && (id < KEYWORDS_MAX));
}

const char *KeyParser::GetKeyById(uint16_t id)
{
    if (!IsKeyValid(id)) {
        return "UNKNOWN";
    }
#if defined(ENABLE_KEY)
    return G_KEYWORD_INFO[id].key;
#else
    return "UNKNOWN";
#endif // ENABLE_KEY
}

uint8_t KeyParser::GetKeyLengthById(uint16_t id)
{
    if (!IsKeyValid(id)) {
        return 0;
    }
    return G_KEYWORD_INFO[id].LENGTH;
}
} // namespace ACELite
} // namespace OHOS
