
#include "column_model_ng.h"
#include "view_stack_processor.h"

#include <iostream>

namespace OHOS{
namespace ACELite {

void ColumnModelNG::Create()
{
   printf("ColumnModelNG::Create()-------\n");
   auto* stack = ViewStackProcessor::GetInstance();

   auto frameNode = FrameNode::GetOrCreateFrameNode("Column", 1, 
        static_cast<std::function<std::shared_ptr<LinearLayoutPattern>()>>(createLinearLayoutPattern));
   if (!frameNode) {
      return;
   }

   stack->Push(frameNode);
   auto pattern = static_pointer_cast<LinearLayoutPattern>(frameNode->GetPattern());
   if (!pattern) {
      return;
   }
   currentPattern_  = pattern;

}

}
}
