#include "layout_property.h"

namespace OHOS{
namespace ACELite {
LayoutProperty::LayoutProperty(std::shared_ptr<UIView>& view)
    : natvieView_(view)
{

}

void LayoutProperty::SetWidth(const CalcLength &width)
{   
    int16_t value = static_cast<int16_t>(width.GetDimensionContainsNegative().Value());

    natvieView_->SetWidth(value);

}

void LayoutProperty::SetHeight(const CalcLength &height)
{
    int16_t value = static_cast<int16_t>(height.GetDimensionContainsNegative().Value());

    natvieView_->SetHeight(value);
}
}
}
