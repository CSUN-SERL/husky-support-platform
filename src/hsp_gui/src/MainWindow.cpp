#include "MainWindow.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>

#include <QTextEdit>
#include <QKeyEvent>
#include <UGVControl.h>

#define ANGULAR_ACCEL 0.5

MainWindow::MainWindow(UGVControl *husky) :
linear_scale(10), // was two // makes it so it goes further
angular_scale(10), // was two and a comma 
linear(0),
angular(0),
model(new QStandardItemModel(this))
{
    widget.setupUi(this);

    this->husky = husky;
    this->numberOfBatteryDisp = 0;

    this->initCoordModel();

    //    batteryLooper = std::thread(&MainWindow::BatteryLooper, this);
    //    batteryLooper.detach();

    int speed = widget.slider_speed->value();
    this->onSpeedValueChanged(speed);
    connect(widget.slider_speed, &QSlider::valueChanged,
            this, &MainWindow::onSpeedValueChanged);
    
    connect(widget.btn_up, &QPushButton::pressed,
            this, &MainWindow::OnUpClicked);
    connect(widget.btn_up, &QPushButton::released,
            this, &MainWindow::OnReleased);

    connect(widget.btn_left, &QPushButton::pressed,
            this, &MainWindow::OnLeftClicked);
    connect(widget.btn_left, &QPushButton::released,
            this, &MainWindow::OnReleased);

    connect(widget.btn_right, &QPushButton::pressed,
            this, &MainWindow::OnRightClicked);
    connect(widget.btn_right, &QPushButton::released,
            this, &MainWindow::OnReleased);

    connect(widget.btn_down, &QPushButton::pressed,
            this, &MainWindow::OnDownClicked);
    connect(widget.btn_down, &QPushButton::released,
            this, &MainWindow::OnReleased);

    connect(widget.close_button, &QPushButton::clicked,
            this, &MainWindow::OnCloseClicked);

    connect(widget.stop_Button, &QPushButton::clicked,
            this, &MainWindow::OnStopClicked);

    connect(widget.btn_arm, &QPushButton::clicked,
            this, &MainWindow::onArmDisarmClicked);

    //    connect(widget.AutoButton, &QPushButton::clicked,
    //            this,&MainWindow::autoClicked);

    connect(widget.Go_Button, &QPushButton::clicked,
            this, &MainWindow::OnGoClicked);
    
}

MainWindow::~MainWindow() {

}

void MainWindow::BatteryLooper() {
    //    ros::Rate sleeper(10);
    //    while(1){
    //        system("rostopic echo /status/charge_estimate | rostopic pub nh/charge_estimate std_msgs/Float64 -1");
    //        
    //    //widget.batteryBar->setValue(std::round(system("rostopic echo /status/charge_estimate")));
    //        sleeper.sleep();
    //    }
    //    sleep(100);
    while (1) {
        int integer = husky->GetBattery();
        widget.batteryBar->setValue(integer);
    }
}

void MainWindow::closeEvent(QCloseEvent * e)
{
    husky->arm(false);
    QMainWindow::closeEvent(e);
    e->accept();
}

void MainWindow::initCoordModel()
{
    QStringList headers({"X", "Y"});
    model->setHorizontalHeaderLabels(headers);
    widget.tablev_coords->setModel(model);
    
    widget.tablev_coords->setItemDelegate(new DoubleValidatorDelegate(this));
    
    connect(widget.btn_add, &QPushButton::clicked,
                this, &MainWindow::onBtnAddClicked);
    
    connect (widget.btn_remove, &QPushButton::clicked,
                this, &MainWindow::onBtnRemoveClicked);
}

void MainWindow::onBtnAddClicked()
{
    QList<QStandardItem*> row({new QStandardItem, new QStandardItem});
    model->appendRow(row);
}

void MainWindow::onBtnRemoveClicked()
{
    int row_count = model->rowCount();
    if(row_count > 1)
    {
        model->removeRow(row_count - 1 );
    }
}

void MainWindow::onSpeedValueChanged(int value)
{
    linear_speed = (double)(value/10.0);
    ROS_INFO_STREAM("Linear Speed: " << linear_speed);
    widget.lbl_linear_speed->setText("Linear Speed: " + QString::number(linear_speed));
}

void MainWindow::ImageCallback(const sensor_msgs::ImageConstPtr& in) {
    ROS_WARN_STREAM("in image callback");

    QImage::Format f = QImage::Format_RGB888;
    QImage img(in->data.data(), in->width, in->height, in->step, f);
    //    img = img.rgbSwapped();

    QPixmap pic = QPixmap::fromImage(img);

    int w = widget.image_frame->width();
    int h = widget.image_frame->height();

    pic = pic.scaled(w, h, Qt::KeepAspectRatio);
    widget.image_frame->setPixmap(pic);
}
//void MainWindow::statusCallBack(const std_msgs::Float64 msg){
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
//  int integer=std::round(msg.data*100);
//widget.batteryBar->setValue(integer);

//}
//not needed for now, maybe.
//void MainWindow::UpdateBatteryBar(double batteryPercentage){
//widget.batteryBar(batteryPercentage);
//}

void MainWindow::TranslateAndPublish() {
    geometry_msgs::Twist twist;
    twist.angular.z = angular_scale * angular;
    twist.linear.x = linear_scale * linear;
    //twist.linear.y = linear_scale * linear; 
    pub_cmd_vel.publish(twist);

    linear = angular = 0;
}

void MainWindow::OnLeftClicked() {
    if(husky->isArmed())
        husky -> turn(ANGULAR_ACCEL);
}

void MainWindow::OnReleased() {
    //widget.textEdit->append("Releasing the button\n");
    husky -> stop();
}

void MainWindow::OnRightClicked() {
    //widget.textEdit->setText("Moving husky to the right. \n");
    if(husky->isArmed())
        husky -> turn(-ANGULAR_ACCEL);
}

void MainWindow::OnUpClicked() {
    //widget.textEdit->setText("Moving husky up. \n");
    ROS_INFO_STREAM("Up Clicked: Husky Armed status" << husky->isArmed());
    ROS_INFO_STREAM("linear_speed: " << linear_speed);
   if(husky->isArmed())
       husky -> crawl(linear_speed);
}

void MainWindow::OnDownClicked() {
    //widget.textEdit->setText("Moving husky down. \n");
    if(husky->isArmed())
        husky->crawl(-linear_speed);
}

void MainWindow::OnCloseClicked() {
    husky->arm(false);
    if(!husky->isArmed())
    {
        this ->close();
    }
    else
    {
        ROS_ERROR_STREAM("ERROR unable to disarm Husky");
    }
}

void MainWindow::OnGoClicked() // this will just make the turtle sim go out 10 spaces
{
    // ROS_WARN_STREAM("in On Go Clicked will go forth 10 spaces");
    //widget.textEdit->setText("Will go forward 10 spaces\n");
    //husky -> crawl((double)ACCEL/2);
    //widget.textEdit->setText("Will go backwards 5 spaces\n");
    //husky -> crawl(-5);
    //linear = 10;
    //angular = 10;
    //this -> TranslateAndPublish();
    
    waypoints.clear();
    for(int i = 0; i < model->rowCount(); i++)
    {
        UGVControl::Point p;
        p.x = model->item(i, 0)->data().toDouble();
        p.y = model->item(i, 1)->data().toDouble();
        waypoints.push_back(p);
    }
    husky->setMission(waypoints);
    husky->startMission();
}

void MainWindow::OnStopClicked() {
    // if you use append itll just add instead of replace the string
    //widget.textEdit->setText("Stopping movement\n");
    husky -> stop();
    //linear = 0;
    //angular = 0;
    //this -> TranslateAndPublish();
}

// testing the input system

void MainWindow::onArmDisarmClicked() {
    //tring text;
    //xt -> 
    //rwidget.textEdit->setText("Moving to location. \n");
    bool disarm = widget.btn_arm->isChecked();
    husky->arm(disarm);
    if(husky->isArmed())
    {
        widget.btn_arm->setText("Disarm");
    }
    else
    {
        widget.btn_arm->setText("Arm");
    }
    
    
    //linear = lat;
    // this -> TranslateAndPublish();
    // angular = longitude;
    //  this -> TranslateAndPublish();
}

//void MainWindow::autoClicked()
//{
//    system("google-chrome https://www.youtube.com/watch?v=dQw4w9WgXcQ");
//}

//
//JG- methods that take in keyboard input.
//Can be modified to take in more keys using additional else if statements.

void MainWindow::keyPressEvent(QKeyEvent* e) {
    QMainWindow::keyPressEvent(e);

    if (e->key() == Qt::Key_Left) {
        this->OnLeftClicked();
    } else if (e->key() == Qt::Key_Up) {
        this->OnUpClicked();
    } else if (e->key() == Qt::Key_Right) {
        this->OnRightClicked();
    } else if (e->key() == Qt::Key_Down) {
        this->OnDownClicked();
    }
    e->accept();
}

void MainWindow::keyReleaseEvent(QKeyEvent* e) {
    if (e->key() == Qt::Key_Left ||
        e->key() == Qt::Key_Up ||
        e->key() == Qt::Key_Right ||
        e->key() == Qt::Key_Down
    ){
        husky -> stop();
    } 

    e->accept();
}

//        void UGVControl::jSONFileEditorBattery(std::string Stringer, std::string buffer){
//           int index= buffer.find("battery_Percentage");
//           //add the chars of batery_percentage and the colon that follows
//           index=index+20;
//           int batteryStatus= UGVControl::GetBattery();
//           std::string batteryString=std::to_string(batteryStatus);
//           //ROS_WARN_STREAM("integer: " << buffer);
//           /*Parameter:   __pos1 Index of first character to replace.
//Parameter:   __n1 Number of characters to be replaced.
//Parameter:   __str String to insert.
//Parameter:   __pos2 Index of first character of str to use.
//Parameter:   __n2 Number of characters from str to use.
//            * */
//           //buffer.replace(index,1,batteryString[0],1);
//           
//           //buffer.replace(index+1,1,batteryString[1],1);
//           buffer[index]=batteryString[0];
//           buffer[index+1]=batteryString[1];
//           std_msgs::String buffer_msg;
//           buffer_msg.data=buffer;
//           //UGVControl::status_pub.publish(buffer_msg);
//           //ROS_WARN_STREAM("integer: " << buffer);
//        
//        }
//        void jSONFileEditorMissionStatus(std::string Stringer, std::string buffer){
//        
//        }
        //void UGVControl::statusCallBack(const husky_msgs::HuskyStatusConstPtr& msg){
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
            
//    int integer = (msg.get()->charge_estimate *100);
//    setBatteryStatus(integer);
//    std::string buffer= UGVControl::jSONFileStringObject();
//    std::string strInteger= UGVControl::toString(integer);
//    UGVControl::jSONFileEditorBattery(strInteger, buffer);
//    
//   
//    //ROS_INFO("HELLO");
//    //ROS_WARN_STREAM("integer: " << integer);
//   
//   
//}

// check if there is a way to send commands to a terminal in qt