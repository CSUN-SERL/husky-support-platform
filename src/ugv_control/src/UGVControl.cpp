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
void UGVControl::BatteryPub(){
    UGVControl::jSONFileEditorMissionStatus();
    UGVControl::status_pub.publish(UGVControl::jsonMsg);
}
void UGVControl::setBatteryStatus(int battery){
      battery_percentage=battery;
}
        
        /*the overridden vehicle_control GetBattery();
        int UGVControl::getBatteryStatus(){
            return state.battery;
            //return batteryStatus;
        }*/
        std::string UGVControl::jSONFileStringObject(){
            
//            std::ifstream file("include/vehicleDoc.txt");
//            std::ostringstream tmp;
//            
//            tmp<<file.rdbuf();
//            std::string s = tmp.str();
             std::ifstream ifs("vehicleDoc.json");
             std::string content( (std::istreambuf_iterator<char>(ifs) ),
                       (std::istreambuf_iterator<char>()    ) );
            std::cout<<content<<std::endl;
            return content;
        
        }
        std::string UGVControl::toString(int integer){
        std::string strInteger=std::to_string(integer);
        return strInteger;
        }
        
        void UGVControl::jSONFileEditorBattery(std::string Stringer, std::string buffer){
           int index= buffer.find("battery_Percentage");
           //add the chars of batery_percentage and the colon that follows
           index=index+20;
           int batteryStatus= UGVControl::GetBattery();
           std::string batteryString=std::to_string(batteryStatus);
           //ROS_WARN_STREAM("integer: " << buffer);
           /*Parameter:   __pos1 Index of first character to replace.
Parameter:   __n1 Number of characters to be replaced.
Parameter:   __str String to insert.
Parameter:   __pos2 Index of first character of str to use.
Parameter:   __n2 Number of characters from str to use.
            * */
           //buffer.replace(index,1,batteryString[0],1);
           
           //buffer.replace(index+1,1,batteryString[1],1);
           buffer[index]=batteryString[0];
           buffer[index+1]=batteryString[1];
           //std_msgs::String buffer_msg;
           UGVControl::jsonMsg.data=buffer;
           //buffer_msg.data=buffer;
           //UGVControl::jsonMsg.assign(buffer_msg);
           //UGVControl::status_pub.publish(buffer_msg);
           //ROS_WARN_STREAM("integer: " << buffer);
        
        }
        void UGVControl::jSONFileEditorMissionStatus(){
        int index= UGVControl::jsonMsg.data.find("mission_Status");
        
        index=index+19;
        if (UGVControl::jsonMsg.data[index]=='f'){
          
           UGVControl::jsonMsg.data[index+1]='t';
           UGVControl::jsonMsg.data[index+2]='r';
           UGVControl::jsonMsg.data[index+3]='u';
           UGVControl::jsonMsg.data[index+4]='e';
           UGVControl::jsonMsg.data[index+5]=' ';
           
           //while(i<=23){
             //  buffer
           //}
        }
        else if (UGVControl::jsonMsg.data[index]=='t'){
         UGVControl::jsonMsg.data[index+1]='f';
           UGVControl::jsonMsg.data[index+2]='a';
           UGVControl::jsonMsg.data[index+3]='l';
           UGVControl::jsonMsg.data[index+4]='s';
           UGVControl::jsonMsg.data[index+5]='e';
        }
           //add the chars of batery_percentage and the colon that follows
           index=index+20;
           int batteryStatus= UGVControl::GetBattery();
           std::string batteryString=std::to_string(batteryStatus);
           UGVControl::BatteryPub();
}
        void UGVControl::statusCallBack(const husky_msgs::HuskyStatusConstPtr& msg){
    //std::cout<<msg.data;
    /*batteryList[numberOfBatteryDisp]=msg.data*100;
    MainWindow::numberOfBatteryDisp++;
    double sum=0;
    if(numberOfBatteryDisp==10){
        for(int i=0;i<sizeof(batteryList);i++){
            sum+=batteryList[i];
    }
        int average=std::round(sum/numberOfBatteryDisp);
        
        widget.batteryBar->setValue(average);
        numberOfBatteryDisp=0;
    }
    else{
        numberOfBatteryDisp++;
    }*/
            
    int integer = (msg.get()->charge_estimate *100);
    setBatteryStatus(integer);
    std::string buffer= UGVControl::jSONFileStringObject();
    std::string strInteger= UGVControl::toString(integer);

     //subscribeLooper=std::thread(&MainWindow::BatteryLooper,this);
    //subscribeLooper.detach();
    
    UGVControl::jSONFileEditorBattery(strInteger, buffer);
    
   
    //ROS_INFO("HELLO");
    //ROS_WARN_STREAM("integer: " << integer);
   
   
}
        /*void UGVControl::subscriberLoop(){
        while(status_pub.getNumSubscribers() == 0){
		//std_msgs::String msg;
		//msg.data = "64.0";
		//ROS_INFO(to_string(msg.data));
		//publish.publish(msg);
		//ros::spinOnce();
		ROS_ERROR("Waiting for subscriber");
		sleep(10);
}*/
void UGVControl::initiateObjects() {
    position = new Position();
    random_msgs = {"Hey", "Hi", "Hello", "Hell NO", "yep"};
}

void UGVControl::initiatePublishers() {
    husky_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
    pub_events = n.advertise<std_msgs::String>("/vehicle_events", 100);
    status_pub= n.advertise<std_msgs::String>("/vehicle_events",10);
}

void UGVControl::initiateSubscribers() {
UGVControl::huskyStatusSubscriber = n.subscribe("/status", 1000, &UGVControl::statusCallBack, this);
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
        UGVControl::jSONFileEditorMissionStatus();
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


