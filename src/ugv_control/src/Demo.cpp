#include "Demo.h"

Demo::Demo(){
    currentPoint = 0;
    points[0][0] = 800.0;
    points[0][1] = 800.0;
    points[1][0] = -800.0;
    points[1][1] = -800.0;
    points[2][0] = 0.0;
    points[2][1] = 0.0;
    demoTimer = nodeHandle.createTimer(ros::Duration(0.1), &Demo::run, this);
}

void Demo::run(const ros::TimerEvent& event){
    if(currentPoint < 3){
        if(husky.hasArrived()){
            husky.moveTo(points[currentPoint][0], points[currentPoint][1]);
            currentPoint++;
        }
    }else{
        demoTimer.stop();
    }
}
 
