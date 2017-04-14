#include "UGVControl.h"



        UGVControl::UGVControl()
        {
            forward = 0;
            rotate = 0;
            this->InitialSetup();
            moveTimer = n.createTimer(ros::Duration(0.1), &UGVControl::move, this);
        }
          UGVControl::~UGVControl()
          {
              
          }

        void UGVControl::crawl(double f){
            forward = f;
        }

        void UGVControl::turn(double r){
            rotate = r;
        }

        void UGVControl::stop(){
            forward = 0;
            rotate = 0;
        }

        void UGVControl::move(const ros::TimerEvent& event)
        {
            geometry_msgs::Twist msg;
            msg.linear.x = forward;
            msg.linear.y = 0.0;
            msg.linear.z = 0.0;
            msg.angular.x = 0.0;
            msg.angular.y = 0.0;
            msg.angular.z = rotate;
            husky_pub.publish(msg);
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
    ROS_INFO("HELLO");
    ROS_WARN_STREAM("integer: " << integer);
   
   
}

        void UGVControl::InitialSetup()
        {
          //publishers
        //  husky_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1000);
          //subscribers
            
          huskyStatusSubscriber = n.subscribe("/status", 1000, &UGVControl::statusCallBack, this);
          //ros::Publisher battery_pub = n.advertise<std_msgs::Float64>("charge_estimate", 1000);
          //location_sub = n.subscribe("husky_velocity_controller/odom", 1000, &UGVControl::LocationCallback, this);
          //laser_sub = n.subscribe("scan", 1000, &UGVControl::LaserCallback, this);
        }
        
        void UGVControl::LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
        {
            laser=*scan;
            for(int i = 0; i < laser.ranges.size(); i++){
            	ROS_INFO("point_of_ranges=[%f] \n", laser.ranges[i]); // this works
           }
        }

        void UGVControl::LocationCallback(const nav_msgs::Odometry::ConstPtr& msg)
        {
          ROS_INFO("Seq: [%d]", msg->header.seq);
          ROS_INFO("Position-> x: [%f], y: [%f], z: [%f]", msg->pose.pose.position.x,msg->pose.pose.position.y, msg->pose.pose.position.z);
          ROS_INFO("Orientation-> x: [%f], y: [%f], z: [%f], w: [%f]", msg->pose.pose.orientation.x, msg->pose.pose.orientation.y, msg->pose.pose.orientation.z, msg->pose.pose.orientation.w);
          ROS_INFO("Vel-> Linear: [%f], Angular: [%f]", msg->twist.twist.linear.x,msg->twist.twist.angular.z);
        }
        
        void UGVControl::setBatteryStatus(int battery){
            batteryStatus=battery;
        }
        
        int UGVControl::getBatteryStatus(){
            return batteryStatus;
        }
        
        

//not needed for now, maybe.
//void MainWindow::UpdateBatteryBar(double batteryPercentage){}



 
//not needed for now, maybe.
//void MainWindow::UpdateBatteryBar(double batteryPercentage){}
   


