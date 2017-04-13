#include "UGVControl.h"

UGVControl::UGVControl() //:
//position(new Position())
{
    this->initiateAttributes();
    this->initiateObjects();
    this->initiatePublishers();
    this->initiateSubscribers();
}

//private------------------------------------------------------------------------
void UGVControl::initiateAttributes() {
    arrived = true;
    forward = 0;
    rotate = 0;
    moveTimer = n.createTimer(ros::Duration(0.1), &UGVControl::move, this);
    moveToTimer = n.createTimer(ros::Duration(0.1), &UGVControl::autoMove, this);
    eventTimer = n.createTimer(ros::Duration(2.0), &UGVControl::publishEvent, this);
    angleCalc = VectorAngleCalculator();
    moveToTimer.stop();
}

void UGVControl::initiateObjects() {
    position = new Position();
    random_msgs = {"Hey", "Hi", "Hello", "Hell NO", "yep" };
}

void UGVControl::initiatePublishers() {
    husky_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
    pub_events = n.advertise<std_msgs::String>("/vehicle_events", 100);
}

void UGVControl::initiateSubscribers() {
    
}

void UGVControl::crawl(double f) {
    forward = f;
}

void UGVControl::turn(double r) {
    rotate = r;
}

void UGVControl::stop() {
    forward = 0;
    rotate = 0;
}

bool UGVControl::hasArrived(){
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

void UGVControl::moveTo(double x, double y){
    arrived = false;
    destination = Destination(x, y, position);
    moveToTimer.start();
}

void UGVControl::autoMove(const ros::TimerEvent& event){
    if(arrived){
        moveToTimer.stop();
        stop();        
    }else{
        moveToDestintion();
    }
    //ROS_INFO("Angular Speed:%f", rotate);
    //ROS_INFO("Linear Speed:%f", forward);
}

void UGVControl::moveToDestintion(){
    if(initiallyAligned){
        Vector dVector = destination.getVector();
        
        double desMag = dVector.mag;
        //ROS_INFO("Destinatin mag.: %f" , desMag); 
        if(desMag < 50){
            crawl(0.0);            
            arrived = true;
        }else{
            crawl(0.2);        
        }
    }
    align();    
}

void UGVControl::publishEvent(const ros::TimerEvent& event)
{
    std_msgs::String s;
    s.data = random_msgs.at(rand() % random_msgs.size());
    pub_events.publish(s);
}

void UGVControl::align(){
    if(isAligned()){
        initiallyAligned = true;
        turn(0.0);        
    }
}

bool UGVControl::isAligned(){
    double tolerance = 5.0;
    Vector pVector = position->getVector();
    Vector dVector = destination.getVector();
    double test = angleCalc.degree(&pVector, &dVector);
    //ROS_INFO("Angle: %f" , test);
    
    if(abs(test) <= tolerance){
        return true;
    }else{
        if(test > 0.0){
            turn(-0.5);
        }else{
            turn(0.5);    
        }
        return false;
    }
}

UGVControl::~UGVControl() {
   delete position; 
}

//void UGVControl::LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
//{
//    laser=*scan;
//    for(int i = 0; i < laser.ranges.size(); i++){
//        ROS_INFO("point_of_ranges=[%f] \n", laser.ranges[i]); // this works
//   }
//}

//void UGVControl::LocationCallback(const nav_msgs::Odometry::ConstPtr& msg)
//{
//  ROS_INFO("Seq: [%d]", msg->header.seq);
//  ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
//  ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
//  ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
//}

