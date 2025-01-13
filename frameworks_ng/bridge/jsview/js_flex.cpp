

#include "js_flex.h"
#include "flex_model_ng.h"

namespace OHOS{
namespace ACELite {
FlexModel* FlexModel::GetInstance()
{
    static FlexModelNG instance;
    return &instance;
}


}
}
