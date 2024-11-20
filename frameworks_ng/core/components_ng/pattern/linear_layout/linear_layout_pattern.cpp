#include "linear_layout_pattern.h"
#include "root_view.h"
#include "common/task_manager.h"

namespace OHOS{
namespace ACELite {
LinearLayoutPattern::LinearLayoutPattern(bool isVertical) 
    : isVertical_(isVertical)
{

}

void LinearLayoutPattern::OnShow(UIView* view) const
{
    return;
    RootView *rootView = RootView::GetInstance();
    if (rootView == nullptr) {
        return;
    }
    //rootView->SetStyle(STYLE_BACKGROUND_COLOR, Color::Yellow().full);
    rootView->RemoveAll();
    rootView->SetPosition(0, 0);
    rootView->SetWidth(1000);
    rootView->SetHeight(1000);
    rootView->Add(nativeView_.get());
    rootView->Focus();
    rootView->Invalidate();

    TaskManager::GetInstance()->TaskHandler();
    printf("LinearLayoutPattern::Show()-----rootVIew=[%p]\n", rootView);
}

void LinearLayoutPattern::CreateNativeView()
{
    FlexLayoutPattern::CreateNativeView();
}

}
}
