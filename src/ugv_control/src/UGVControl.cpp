#include "UGVControl.h"


UGVControl::UGVControl() {
    this->initiateAttributes();
    this->initiateObjects();
    this->initiatePublishers();
    this->initiateSubscribers();
}

//private------------------------------------------------------------------------

void UGVControl::initiateAttributes() {
    arrived = true;
    armed = false;
    isOnMission = false;
    forward = 0;
    rotate = 0;
    moveTimer = n.createTimer(ros::Duration(0.1), &UGVControl::move, this);
    moveTimer.stop();
    moveToTimer = n.createTimer(ros::Duration(0.1), &UGVControl::autoMove, this);
    moveToTimer.stop();
    //eventTimer = n.createTimer(ros::Duration(2.0), &UGVControl::publishEvent, this);
    angleCalc = VectorAngleCalculator();
}

void UGVControl::initiateObjects() {
    position = new Position();
    random_msgs = {"Hey", "Hi", "Hello", "Hell NO", "yep"};
}

void UGVControl::initiatePublishers() {
    husky_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
    pub_events = n.advertise<std_msgs::String>("/vehicle_events", 100);
}

void UGVControl::initiateSubscribers() {

}

void UGVControl::setMission(const std::vector<Point>& waypoints)
{
    this->waypoints = waypoints;
}

void UGVControl::startMission()
{    
    isOnMission = true;
    currentWaypoint = 0;
    moveToNextWayPoint();
}

void UGVControl::stopMission()
{    
    this->stop();
}

void UGVControl::removeMission(){
    this->waypoints.clear();
    isOnMission = false;
}

void UGVControl::moveToNextWayPoint(){
    if(currentWaypoint < this->waypoints.size()){
        Point currentPoint = this->waypoints.at(currentWaypoint);
        ROS_WARN_STREAM("Next Point - X:" << currentPoint.x << " Y:" << currentPoint.y);
        currentWaypoint++;
        moveTo(currentPoint.x, currentPoint.y);
    }else{
        removeMission();
    }
}

void UGVControl::crawl(double f) {
    if (!armed) return;
    forward = f;
    moveTimer.start();
}

void UGVControl::turn(double r) {
    if (!armed) return;
    rotate = r;
    moveTimer.start();
}

void UGVControl::stop() {
    forward = 0;
    rotate = 0;
    moveTimer.stop();
    moveToTimer.stop();
}

bool UGVControl::arm(bool arm ) {
    armed = arm;
    ROS_WARN_STREAM("Husky arm status: " << armed);
    if(armed == false)
    {
        stop(); 
    }
    return armed;
}

bool UGVControl::isArmed() {
    return armed;
}

bool UGVControl::hasArrived() {
    return arrived;
}

void UGVControl::move(const ros::TimerEvent& event) {
    geometry_msgs::Twist msg;
    msg.linear.x = forward;
    msg.linear.y = 0.0;
    msg.linear.z = 0.0;
    msg.angular.x = 0.0;
    msg.angular.y = 0.0;
    msg.angular.z = rotate;
    husky_pub.publish(msg);
}

void UGVControl::moveTo(double x, double y) {
    if (!armed) return;
    arrived = false;
    initiallyAligned = false;
    destination = Destination(x, y, position);
    moveToTimer.start();
}

void UGVControl::autoMove(const ros::TimerEvent& event) {
    if (arrived) {
        stop();
        moveToNextWayPoint();
    } else {
        moveToDestintion();
    }
}

void UGVControl::moveToDestintion() {
    Vector dVector = destination.getVector();
    double desMag = dVector.mag; // Destination vector magnitude
    if (desMag < destinationTolerance) {
        arrived = true;
    } else {
        if (initiallyAligned) crawl(autoLinearSpeed);
    }
    align();
}

void UGVControl::publishEvent(const ros::TimerEvent& event) {
    std_msgs::String s;
    s.data = random_msgs.at(rand() % random_msgs.size());
    pub_events.publish(s);
}

void UGVControl::align() {
    if (isAligned()) {
        initiallyAligned = true;
        turn(0.0);
    }
}

bool UGVControl::isAligned() {
    Vector pVector = position->getVector();
    Vector dVector = destination.getVector();
    double vectorsAngle = angleCalc.degree(&pVector, &dVector);
    double vecotrsAngleMag = abs(vectorsAngle);
    double angularSpeed = calcAutoAngularSpeed(vecotrsAngleMag);        
    
    if (vecotrsAngleMag <= angularTolerance) {
        return true;
    } else {
        if (dVector.mag < 200) {
            forward = 0.0;
            initiallyAligned = false;
        }
        if (vectorsAngle > 0.0) {
            turn(-1.0 * angularSpeed);
        } else {
            turn(angularSpeed);
        }
        return false;
    }
}

double UGVControl::calcAutoAngularSpeed(double vectorsAngle){
    double angularSpeed;
    if(vectorsAngle < 20.0 && vectorsAngle >= 10.0){
        angularSpeed = 0.3;
    }else if(vectorsAngle < 10.0 && vectorsAngle >= 5.0){
        angularSpeed = 0.2;
    }else if(vectorsAngle < 5.0){
        angularSpeed = 0.1;
    }else{
        angularSpeed = autoAngularSpeed;
    }
    return angularSpeed;
}

UGVControl::~UGVControl() {
    delete position;
}


