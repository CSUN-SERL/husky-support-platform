
#include "MainWindow.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <QTextEdit>

MainWindow::MainWindow():
    linear_scale(2),
    angular_scale(2),
    linear(0),
    angular(0)
{
    widget.setupUi(this);

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/turtle1/cmd_vel", 1);

    
    image_transport::ImageTransport it{nh};
    
    sub_img = it.subscribe("/usb_cam/image_raw", 100, &MainWindow::ImageCallback, this);


    connect(widget.btn_up, &QPushButton::clicked,
            this, &MainWindow::OnUpClicked);
    connect(widget.btn_left, &QPushButton::clicked,
            this, &MainWindow::OnLeftClicked);
    connect(widget.btn_right, &QPushButton::clicked,
            this, &MainWindow::OnRightClicked);
    connect(widget.btn_down, &QPushButton::clicked,
            this, &MainWindow::OnDownClicked);
    connect(widget.close_button, &QPushButton::clicked,
            this, &MainWindow::OnCloseClicked);
    connect(widget.Go_Button, &QPushButton::clicked,
            this, &MainWindow::OnGoClicked);
    connect(widget.stop_Button, &QPushButton::clicked,
            this, &MainWindow::OnStopClicked);
    connect(widget.loc_Button, &QPushButton::clicked,
            this,&MainWindow::loc_ButtonClicked);
  
    /* connect(widget.Go_Button, &QPushButton::clicked,
            this, &QProgressBar::value(100)); */
    widget.textEdit->setText("Hello I am a Log Box\n");
   
}

MainWindow::~MainWindow()
{
    
}

void MainWindow::ImageCallback(const sensor_msgs::ImageConstPtr& in)
{
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
    widget.textEdit->append("I am going to the left\n");
    angular = 1;
    this->TranslateAndPublish();
}

void MainWindow::OnRightClicked()
{
    widget.textEdit->append("I am going to the right\n");
    angular = -1;
    this->TranslateAndPublish();
}

void MainWindow::OnUpClicked(bool checked)
{
    widget.textEdit->append("I am going up, on a Tuesday!\n");
    if(checked)
    {
    linear = 1;
    this->TranslateAndPublish();
    }
}

void MainWindow::OnDownClicked()
{
    widget.textEdit->append("I am going down\n");
    linear = -1;
    this->TranslateAndPublish();
}

void MainWindow::OnCloseClicked()
{
    
    this ->close();
}

void MainWindow::OnGoClicked() // this will just make the turtle sim go out 10 spaces
{
    ROS_WARN_STREAM("in On Go Clicked will go forth 10 spaces");
    widget.textEdit->append("Will go forth 10 space and to the right\n");
    linear = 10;
    angular = 10;
    this -> TranslateAndPublish();
}

void MainWindow::OnStopClicked()
{
    widget.textEdit->append("STOPPING STOPPING\n");
    linear = 0;
    angular = 0;
    this -> TranslateAndPublish();
}

// testing the input system
void MainWindow::loc_ButtonClicked()
{
    //tring text;
    //xt -> 
    int lat = 0;
    int longitude = 0;
    lat = widget.LatBox -> text().toInt();
    longitude = widget.LongBox -> text().toInt();
    linear = lat;
   // this -> TranslateAndPublish();
    angular = longitude;
    this -> TranslateAndPublish();
}

// check if there is a way to send commands to a terminal in qt