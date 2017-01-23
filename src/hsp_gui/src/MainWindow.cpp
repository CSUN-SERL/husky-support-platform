#include "MainWindow.h"
#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <QTextEdit>
#include <QKeyEvent>
#include "UGVControl.h"




MainWindow::MainWindow(UGVControl *husky):
    linear_scale(10),// was two // makes it so it goes further
    angular_scale(10), // was two and a comma 
    linear(0),
    angular(0)

{
    
    widget.setupUi(this);
    this->husky = husky;

    pub_cmd_vel = nh.advertise<geometry_msgs::Twist>("/husky_velocity_controller/cmd_vel", 1);

    
    image_transport::ImageTransport it{nh};
    
    sub_img = it.subscribe("/usb_cam/image_raw", 100, &MainWindow::ImageCallback, this);

// going to qt creator and taking off focus policy, was at strong focus
  //  connect(widget.btn_up, &QWidget::keyPressEvent()
    //        this, &MainWindow::OnUpClicked);
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
    
    connect(widget.Go_Button, &QPushButton::clicked,
            this, &MainWindow::OnGoClicked);
    //connect(widget.Go_Button, &QPushButton::released,
       //     this, &MainWindow::OnReleased);
    
    connect(widget.stop_Button, &QPushButton::clicked,
            this, &MainWindow::OnStopClicked);
    
    connect(widget.loc_Button, &QPushButton::pressed,
            this,&MainWindow::loc_ButtonClicked);
    connect(widget.loc_Button, &QPushButton::released,
            this,&MainWindow::OnReleased);
    
    connect(widget.AutoButton, &QPushButton::clicked,
            this,&MainWindow::autoClicked);
  
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
    //twist.linear.y = linear_scale * linear; 
    pub_cmd_vel.publish(twist);
    
    linear = angular = 0;
}

void MainWindow::OnLeftClicked()
{   
    widget.textEdit->setText("Moving husky to the left. \n");
    husky -> turn(-5);
}

void MainWindow::OnReleased()
{
    widget.textEdit->append("Releasing the button\n");
    husky -> stop();
}

void MainWindow::OnRightClicked()
{
    widget.textEdit->setText("Moving husky to the right. \n");
    husky -> turn(5);
}

void MainWindow::OnUpClicked()
{
    widget.textEdit->setText("Moving husky up. \n");
    husky -> crawl(10);
    
}

void MainWindow::OnDownClicked()
{
    widget.textEdit->setText("Moving husky down. \n");
    husky -> crawl(-10);
}

void MainWindow::OnCloseClicked()
{
  
   this ->close();
   // system("rosnode kill usb_cam");
    //system("rosnode kill image_view");
    
}

void MainWindow::OnGoClicked() // this will just make the turtle sim go out 10 spaces
{
   // ROS_WARN_STREAM("in On Go Clicked will go forth 10 spaces");
    widget.textEdit->setText("Will go forward 10 spaces\n");
    husky -> crawl(10);
    //widget.textEdit->setText("Will go backwards 5 spaces\n");
    //husky -> crawl(-5);
    //linear = 10;
    //angular = 10;
    //this -> TranslateAndPublish();
}

void MainWindow::OnStopClicked()
{
    // if you use append itll just add instead of replace the string
    widget.textEdit->setText("Stopping movement\n");
     husky -> stop();
    //linear = 0;
    //angular = 0;
    //this -> TranslateAndPublish();
}

// testing the input system
void MainWindow::loc_ButtonClicked()
{ 
    //tring text;
    //xt -> 
    widget.textEdit->setText("Moving to location. \n");
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

void MainWindow::autoClicked()
{
    system("google-chrome https://www.youtube.com/watch?v=dQw4w9WgXcQ");
}

// check if there is a way to send commands to a terminal in qt