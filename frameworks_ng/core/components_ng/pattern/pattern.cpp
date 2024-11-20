#include "pattern.h"
#include "root_view.h"
#include "common/task_manager.h"

namespace OHOS{
namespace ACELite {

Pattern::Pattern()
{
}

void Pattern::SetWidth(const int16_t &width)
{   
    printf("Pattern::SetWidth----width=[%d]\n", width);
    if (!nativeView_) {
        return;
    }
    nativeView_->SetWidth(width);
}

void Pattern::SetHeight(const int16_t &height)
{
    printf("Pattern::SetHeight----height=[%d]\n", height);
    if (!nativeView_) {
        return;
    }
    nativeView_->SetHeight(height);
}

bool Pattern::ShowPage()
{
    printf("Pattern::ShowPage---\n");
    RootView *rootView = RootView::GetInstance();
    if (rootView == nullptr) {
        return false;
    }
    rootView->RemoveAll();
    rootView->SetPosition(0, 0);
    nativeView_->SetPosition(100, 100, 100, 100);
    nativeView_->SetWidth(500);
    nativeView_->SetHeight(500);
    nativeView_->SetStyle(STYLE_BACKGROUND_COLOR, Color::Yellow().full);
    //rootView->SetStyle(STYLE_BACKGROUND_COLOR, Color::Yellow().full);
    rootView->Add(nativeView_.get());
    rootView->Focus();
    rootView->Invalidate();
    TaskManager::GetInstance()->TaskHandler();

    return true;
}

void Pattern::SetBackgroundColor(const ColorType& color)
{
    if (!nativeView_) {
        return;
    }

    nativeView_->SetStyle(STYLE_BACKGROUND_COLOR, color.full);
}

void Pattern::SetPadding(const int64_t& value)
{
    if (!nativeView_) {
        return;
    }
    
    nativeView_->SetStyle(STYLE_PADDING_LEFT, value);
    nativeView_->SetStyle(STYLE_PADDING_TOP, value);  
    nativeView_->SetStyle(STYLE_PADDING_RIGHT, value);
    nativeView_->SetStyle(STYLE_PADDING_BOTTOM, value);
}

void Pattern::SetMargin(const int64_t& value)
{
    if (!nativeView_) {
        return;
    }

    nativeView_->SetStyle(STYLE_MARGIN_LEFT, value);
    nativeView_->SetStyle(STYLE_MARGIN_TOP, value);  
    nativeView_->SetStyle(STYLE_MARGIN_RIGHT, value);

    nativeView_->SetStyle(STYLE_MARGIN_BOTTOM, value);
}

}
}
