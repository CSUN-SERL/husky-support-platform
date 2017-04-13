#include "Position.h"
#include <iostream>
#include "ros/ros.h"
#include "Vector.h"
#include "Destination.h"
#include "VectorAngleCalculator.h"

//#include <thread>

void tTest() {
    system("roslaunch vrpn_client_ros sample.launch server:=192.168.1.41");
}

int main(int argc, char **argv) {
    //  std::thread test;
    //  test = std::thread(tTest);
    //  test.detach();

    ros::init(argc, argv, "position_tester");
    Position p = Position(true);
    Vector pv = p.getVector();
    ROS_INFO("Position: %f,%f,%f", pv.x, pv.y, pv.mag);

    Destination d = Destination(0.0, 1.0, &p);
    Vector dv = d.getVector();
    ROS_INFO("Destination: %f,%f,%f", dv.x, dv.y, dv.mag);
    VectorAngleCalculator vCalc = VectorAngleCalculator();
    ROS_INFO("Degree: %f\n", vCalc.degree(&dv, &pv));

    d = Destination(-1.0, 1.0, &p);
    dv = d.getVector();
    ROS_INFO("Destination: %f,%f,%f", dv.x, dv.y, dv.mag);
    vCalc = VectorAngleCalculator();
    ROS_INFO("Degree: %f\n", vCalc.degree(&dv, &pv));


    d = Destination(1.0, 1.0, &p);
    dv = d.getVector();
    ROS_INFO("Destination: %f,%f,%f", dv.x, dv.y, dv.mag);
    vCalc = VectorAngleCalculator();
    ROS_INFO("Degree: %f\n", vCalc.degree(&dv, &pv));


    d = Destination(-1.0, 0.0, &p);
    dv = d.getVector();
    ROS_INFO("Destination: %f,%f,%f", dv.x, dv.y, dv.mag);
    vCalc = VectorAngleCalculator();
    ROS_INFO("Degree: %f\n", vCalc.degree(&dv, &pv));


    d = Destination(-1.0, -1.0, &p);
    dv = d.getVector();
    ROS_INFO("Destination: %f,%f,%f", dv.x, dv.y, dv.mag);
    vCalc = VectorAngleCalculator();
    ROS_INFO("Degree: %f\n", vCalc.degree(&dv, &pv));


    d = Destination(0.0, -1.0, &p);
    dv = d.getVector();
    ROS_INFO("Destination: %f,%f,%f", dv.x, dv.y, dv.mag);
    vCalc = VectorAngleCalculator();
    ROS_INFO("Degree: %f\n", vCalc.degree(&dv, &pv));



    d = Destination(1.0, -1.0, &p);
    dv = d.getVector();
    ROS_INFO("Destination: %f,%f,%f", dv.x, dv.y, dv.mag);
    vCalc = VectorAngleCalculator();
    ROS_INFO("Degree: %f\n", vCalc.degree(&dv, &pv));

    ros::spin();
    return 0;
}
