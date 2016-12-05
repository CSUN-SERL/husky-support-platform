
#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "ui_MainWindow.h"
#include <ros/ros.h>
#include <sensor_msgs/Image.h> // using this to get the messages from usb cam
#include <image_transport/image_transport.h> // need this to convert or transport the images
#include "UGVControl.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(UGVControl *husky);
    virtual ~MainWindow();
    
    void ImageCallback(const sensor_msgs::ImageConstPtr& msg);
    
public slots:
    void OnLeftClicked();
    void OnRightClicked();
    void OnUpClicked();
    void OnDownClicked();
    void OnCloseClicked();
    void OnGoClicked();
    void OnStopClicked();
    //test
    void loc_ButtonClicked();
    void autoClicked();
    void OnReleased();
        
private:
    UGVControl *husky;
    Ui::MainWindow widget;
    ros::NodeHandle nh;
    ros::Publisher pub_cmd_vel;
    image_transport::Subscriber sub_img;
    
    double linear,
           angular,
           linear_scale,
           angular_scale;
    
    void TranslateAndPublish();
};

#endif /* _MAINWINDOW_H */
