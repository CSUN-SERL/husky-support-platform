#include "UGVControl.h"



       /* UGVControl::UGVControl(int id)
        {
           
        }*/

//VehicleControl overriden methods
void UGVControl::Arm(bool value){
    //gcs::State.armed=value;
    vehicleInfo.state.armed=value;
}
bool UGVControl::IsArmed(){
    return vehicleInfo.state.armed;
    //return gcs::State.armed;
    
}

          UGVControl::~UGVControl()
          {

          }

        void UGVControl::crawl(double f)
        {
            forward = f;
        }

        void UGVControl::turn(double r)
        {
            rotate = r;
        }

        void UGVControl::stop()
        {
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
void UGVControl::BatteryPub(){
    UGVControl::status_pub.publish(UGVControl::jsonMsg);
}
        void UGVControl::setBatteryStatus(int battery){
            vehicleInfo.state.battery=battery;
            // batteryStatus=battery;

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
           /*Parameter:   __pos1 Index of first character to replace.
Parameter:   __n1 Number of characters to be replaced.
Parameter:   __str String to insert.
Parameter:   __pos2 Index of first character of str to use.
Parameter:   __n2 Number of characters from str to use.
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
        void UGVControl::jSONFileEditorMissionStatus(std::string Stringer){
        int index= UGVControl::jsonMsg.data.find("mission_Status");
        if (UGVControl::jsonMsg.data[19]='f'){
          
           UGVControl::jsonMsg.data[19]='t';
           UGVControl::jsonMsg.data[20]='r';
           UGVControl::jsonMsg.data[21]='u';
           UGVControl::jsonMsg.data[22]='e';
           UGVControl::jsonMsg.data[23]=' ';
           
           //while(i<=23){
             //  buffer
           //}
        }
        else if (UGVControl::jsonMsg.data[19]='t'){
         UGVControl::jsonMsg.data[19]='f';
           UGVControl::jsonMsg.data[20]='a';
           UGVControl::jsonMsg.data[21]='l';
           UGVControl::jsonMsg.data[22]='s';
           UGVControl::jsonMsg.data[23]='e';
        }
           //add the chars of batery_percentage and the colon that follows
           index=index+20;
           int batteryStatus= UGVControl::GetBattery();
           std::string batteryString=std::to_string(batteryStatus);
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
        


        void UGVControl::InitialSetup()
        {
          //publishers
            //batteryStatus= system("rostopic echo /status/charge_estimate");
          husky_pub = n.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 10);
          status_pub= n.advertise<std_msgs::String>("penis",10);
          
          //subscribers
          //&UGVControl::statusCallBack()
          huskyStatusSubscriber = n.subscribe("/status", 1000, &UGVControl::statusCallBack, this);
         //huskyStatusSubscriber= n.subscribe("/status/charge_estimate",10,&UGVControl::statusCallBack,this);
          //location_sub = n.subscribe("husky_velocity_controller/odom", 1000, &UGVControl::LocationCallback, this);
          //laser_sub = n.subscribe("scan", 1000, &UGVControl::LaserCallback, this);
         
        }

        void UGVControl::LaserCallback(const sensor_msgs::LaserScan::ConstPtr& scan)
        {
            laser=*scan;
            for(int i = 0; i < laser.ranges.size(); i++)
            {
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
        /*void UGVControl::setBatteryStatus(int battery){
            batteryStatus=battery;
        }
        int UGVControl::getBatteryStatus(){
        return batteryStatus;
        }
        void UGVControl::statusCallBack(const std_msgs::Float64::ConstPtr& msg){
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
            
    //int integer=std::round(msg->data*100);
   
   
   
//}

//not needed for now, maybe.
//void MainWindow::UpdateBatteryBar(double batteryPercentage){}



 
//not needed for now, maybe.
//void MainWindow::UpdateBatteryBar(double batteryPercentage){}




