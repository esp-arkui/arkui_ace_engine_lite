#include "view_abstract_model_ng.h"
namespace OHOS{
namespace ACELite {

void ViewAbstractModelNG::SetWidth(const int16_t& width)
{
    ViewAbstract::SetWidth(width);
}

void ViewAbstractModelNG::SetHeight(const int16_t& height)
{
    ViewAbstract::SetHeight(height);
}

bool ViewAbstractModelNG::ShowPage()
{
    return ViewAbstract::ShowPage();
}

void ViewAbstractModelNG::SetBackgroundColor(const ColorType& color)
{
    //ViewAbstract::SetBackgroundColor(color);
}

void ViewAbstractModelNG::SetPadding(const int64_t& value)
{
    //ViewAbstract::SetPadding(value);
}

void ViewAbstractModelNG::SetMargin(const int64_t& value)
{
    //ViewAbstract::SetMargin(value);
}
}
}
