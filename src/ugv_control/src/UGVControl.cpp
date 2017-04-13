#include "UGVControl.h"
#include "Demo.h"

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
    forward = 0;
    rotate = 0;
    moveTimer = n.createTimer(ros::Duration(0.1), &UGVControl::move, this);
    moveTimer.stop();
    moveToTimer = n.createTimer(ros::Duration(0.1), &UGVControl::autoMove, this);
    moveToTimer.stop();
    eventTimer = n.createTimer(ros::Duration(2.0), &UGVControl::publishEvent, this);
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
    armed = false;
    moveTimer.stop();
}

bool UGVControl::arm() {
    armed = true;
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
    if(!armed) return;
    arrived = false;
    initiallyAligned = false;
    destination = Destination(x, y, position);
    moveToTimer.start();
}

void UGVControl::autoMove(const ros::TimerEvent& event) {
    if (arrived) {
        stop();
    } else {
        moveToDestintion();
    }
}

void UGVControl::moveToDestintion() {
    if (initiallyAligned) {
        Vector dVector = destination.getVector();
        double desMag = dVector.mag; // Destination vector magnitude
        if (desMag < destinationTolerance) {
            arrived = true;
        } else {
            crawl(autoLinearSpeed);
        }
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
    double angleCheck = angleCalc.degree(&pVector, &dVector);

    if (abs(angleCheck) <= angularTolerance) {
        return true;
    } else {
        if (angleCheck > 0.0) {
            turn(-1.0 * autoAngularSpeed);
        } else {
            turn(autoAngularSpeed);
        }
        return false;
    }
}

UGVControl::~UGVControl() {
    delete position;
}


