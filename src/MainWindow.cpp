#include "MainWindow.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <QTextEdit>
#include <QKeyEvent>
#include "UGVControl.h"
#include <string.h>

MainWindow::MainWindow(UGVControl *husky):
    linear_scale(10),// was two // makes it so it goes further
    angular_scale(10),// was two and a comma 
    linear(0),
    angular(0)

{
    
    widget.setupUi(this);
    this->husky = husky;

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 100);
    //pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/joy_teleop/cmd_vel", 1);
    
    image_transport::ImageTransport it{nh};
    
    sub_img = it.subscribe("/axis/image_raw_out", 1000, &MainWindow::ImageCallback, this);    
    //sub_img = it.subscribe("/usb_cam/image_raw", 100, &MainWindow::ImageCallback, this);

    connect(widget.UpButton, &QPushButton::pressed,
            this, &MainWindow::OnUpClicked);
    connect(widget.UpButton, &QPushButton::released,
            this, &MainWindow::OnReleased);
    
    connect(widget.LeftButton, &QPushButton::pressed,
            this, &MainWindow::OnLeftClicked);
    connect(widget.LeftButton, &QPushButton::released,
            this, &MainWindow::OnReleased);
    
    connect(widget.RightButton, &QPushButton::pressed,
            this, &MainWindow::OnRightClicked);
    connect(widget.RightButton, &QPushButton::released,
            this, &MainWindow::OnReleased);
    
    connect(widget.DownButton, &QPushButton::pressed,
            this, &MainWindow::OnDownClicked);
    connect(widget.DownButton, &QPushButton::released,
            this, &MainWindow::OnReleased);
    
   // connect(widget.CloseButton, &QPushButton::clicked,
     //       this, &MainWindow::OnCloseClicked);
    
    connect(widget.GoButton, &QPushButton::clicked,
            this, &MainWindow::OnGoClicked);
    
       connect(widget.LocButton, &QPushButton::pressed,
            this,&MainWindow::LocButtonClicked);
    connect(widget.LocButton, &QPushButton::released,
            this,&MainWindow::OnReleased);
    
    //connect(widget.go_Button, &QPushButton::released,
       //     this, &MainWindow::OnReleased);
    
    connect(widget.StopButton, &QPushButton::clicked,
            this, &MainWindow::OnStopClicked);
    
    /*connect(widget.BatteryBar, &QPushButton::,
            this, &MainWindow::UpdateButtonClicked);
    /* connect(widget.update_Button, &QPushButton::pressed,
            this,&MainWindow::UpdateButtonClicked);
    connect(widget.update_Button, &QPushButton::released,
            this,&MainWindow::OnReleased); 
    
    connect(widget.auto_Button, &QPushButton::clicked,
            this,&MainWindow::AutoButtonClicked); */
    
    widget.TextEditBox->setText("Hello I am a Log Box\n");
   
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::ImageCallback(const sensor_msgs::ImageConstPtr& in)
{
    // ROS_WARN_STREAM("in image callback");
    
    QImage::Format f = QImage::Format_RGB888;
    QImage img(in->data.data(), in->width, in->height, in->step, f);
    img = img.rgbSwapped();
    
    QPixmap pic = QPixmap::fromImage(img);
    
    int w = widget.image_frame->width();
    int h = widget.image_frame->height();
    
    pic = pic.scaled(w, h, Qt::KeepAspectRatio);
    widget.image_frame->setPixmap(pic);
}

void MainWindow::TranslateAndPublish()
{
    geometry_msgs::Twist twist;
    twist.angular.z = angular_scale * angular;
    twist.linear.x = linear_scale * linear;
    pub_cmd_vel.publish(twist);
    
    linear = angular = 0;
}


void MainWindow::OnLeftClicked()
{   
    widget.TextEditBox->append("Moving husky to the left. \n");
    double spin = 0;
    double forward = 0;
    spin = widget.AngularSpeedLCD -> value();
    forward = widget.LinearSpeedLCD -> value();
    
    husky -> crawl(forward);
    husky -> turn(spin);
}

void MainWindow::OnReleased()
{
    widget.TextEditBox->insertPlainText("Releasing the button\n");
    husky -> stop();
}

void MainWindow::OnRightClicked()
{
    widget.TextEditBox->insertPlainText("Moving husky to the right. \n");
    
    double spin = 0;
    spin = widget.AngularSpeedLCD -> value();
    husky -> turn((-1 * spin));
}

void MainWindow::OnUpClicked()
{
    widget.TextEditBox->insertPlainText("Moving husky up. \n");
    
    double forward = 0;
    forward = widget.LinearSpeedLCD -> value();
    
    husky -> crawl(forward);
}

void MainWindow::OnDownClicked()
{
    widget.TextEditBox->insertPlainText("Moving husky down. \n");
   
    double forward = 0;
    forward = widget.LinearSpeedLCD -> value();
    
    husky -> crawl((-1 * forward));
}

void MainWindow::OnCloseClicked()
{
   this ->close();
}

void MainWindow::OnGoClicked()
{
   // ROS_WARN_STREAM("in On Go Clicked will go forth 10 spaces");
    widget.TextEditBox->insertPlainText("Will go forward until stop is hit!\n");
    husky -> crawl(10);
}

void MainWindow::OnStopClicked()
{
    // if you use append itll just add instead of replace the string
    widget.TextEditBox->insertPlainText("Stopping movement\n");
   // std_msgs::Float64 work = husky -> battery();
   // double test = husky -> battery();
    int batt;
   // batt = static_cast<int>(work * 100 + .5);
    //widget.TextEditBox->insertPlainText(work);
   // ROS_WARN_STREAM(work);
   // widget.BatteryBar ->setValue(batt);
    //char arr[sizeof(test)];
    //memcpy(&arr,&test,sizeof(test));
    //std::string str = arr;
    //widget.TextEditBox->insertPlainText(str);
   // widget.TextEditBox->insertPlainText(QString::number(test));
    husky -> stop();
}

void MainWindow::UpdateButtonClicked()
{ 
    widget.TextEditBox->insertPlainText("Moving to location. \n");
    double lat = 0;
    double longitude = 0;
    longitude = widget.LinearSpeedLCD -> value();
    
    husky -> crawl(longitude);
    husky -> turn(lat);
}

void MainWindow::LocButtonClicked()
{ 
    //tring text;
    //xt -> 
    widget.TextEditBox->setText("Moving to location. \n");
    double lat = 0;
    double longitude = 0;
    lat = widget.LatBox -> text().toDouble();
    longitude = widget.LongBox -> text().toDouble();
    husky -> crawl(lat);
    husky -> turn(longitude);
    //linear = lat;
   // this -> TranslateAndPublish();
   // angular = longitude;
  //  this -> TranslateAndPublish();
}

void MainWindow::keyPressEvent(QKeyEvent* e)
 {
        //if(e)
    if (e->key() == Qt::Key_Left)
   {
        this->OnLeftClicked();

    }
    else if (e->key() == Qt::Key_Up)
    {
        this->OnUpClicked();

    }
    else if (e->key() == Qt::Key_Right)
    {
        this->OnRightClicked();
    }
    else if (e->key() == Qt::Key_Down)
    {
         this->OnDownClicked();

    }
}
void MainWindow::keyReleaseEvent(QKeyEvent* e)
{
    widget.TextEditBox->append("Releasing the button\n");
    husky -> stop();
}

void MainWindow::AutoButtonClicked()
{
    system("google-chrome https://www.youtube.com/watch?v=dQw4w9WgXcQ");
}