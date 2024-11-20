#include "text_pattern.h"

namespace OHOS{
namespace ACELite {

TextPattern::TextPattern()
{

}

TextPattern::~TextPattern()
{
    printf("TextPattern::~TextPattern");
}

void TextPattern::CreateNativeView()
{
    nativeView_ = static_pointer_cast<UIView>(make_shared<UILabel>());
}

void TextPattern::SetText(const std::string& content)
{
    std::shared_ptr<UILabel> label = static_pointer_cast<UILabel>(nativeView_);
    if (!label) {
        return;
    }
    label->SetText(content.c_str());
}


}
}
