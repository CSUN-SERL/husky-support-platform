#include <lcar_msgs/ui_adapter.h>

namespace gcs 
{   
    UIAdapter::UIAdapter(){ }
    
    UIAdapter::~UIAdapter(){ }
    
    UIAdapter * UIAdapter::Instance()
    {
        if(!instance)
            instance = new UIAdapter();
        
        return instance;
    }
    
    UIAdapter *UIAdapter::instance = nullptr;
}
    