#ifndef ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_TEXT_TEXT_MODEL_NG_H
#define ACE_ENGINE_LITE_FRAMEWORKS_NG_BRIDGE_JSVIEW_MODELS_PARTERN_TEXT_TEXT_MODEL_NG_H

#include "text_model.h"
#include "text_pattern.h"
#include <memory>
namespace OHOS{
namespace ACELite {
class TextModelNG : public TextModel {
public:
    void Create(const std::string& content) override;

    static std::shared_ptr<TextPattern> createTextPattern() {
        auto pattern = std::make_shared<TextPattern>();
        if (pattern) {
            pattern->CreateNativeView();
        }
        return pattern;
    }

private:
    std::shared_ptr<TextPattern> currentPattern_;

};
}
}

#endif
