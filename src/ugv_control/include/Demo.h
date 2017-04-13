#ifndef DEMO_H
#define DEMO_H

#include "UGVControl.h"

class Demo{

    public:
        Demo();
        
    private:
        int currentPoint;
        double points[3][2];
        ros::Timer demoTimer;
        ros::NodeHandle nodeHandle;
        UGVControl husky;
        void run(const ros::TimerEvent& event);
                
};

#endif /* DEMO_H */
