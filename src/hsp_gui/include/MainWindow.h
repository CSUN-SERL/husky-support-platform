
#ifndef _MAINWINDOW_H
#define _MAINWINDOW_H

#include "ui_MainWindow.h"
#include <QLineEdit>
#include <QDoubleValidator>
#include <QStandardItemModel>
#include <QItemDelegate>
#include <ros/ros.h>
#include <sensor_msgs/Image.h> // using this to get the messages from usb cam
#include <image_transport/image_transport.h> // need this to convert or transport the images
#include "UGVControl.h"
#include <std_msgs/Float64.h> //use this to get battery status messages JG
#include <thread>
#include <lcar_msgs/ui_adapter.h>
#include <voice_recognition/VoiceRecognition.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(UGVControl *husky);
    virtual ~MainWindow();
    
    void ImageCallback(const sensor_msgs::ImageConstPtr& msg);
  // void statusCallBack(const std_msgs::Float64 msg);
    void UpdateBatteryBar(double batteryPercentage);
    void keyPressEvent(QKeyEvent* e) override;
    void keyReleaseEvent(QKeyEvent* e)override;
    void  BatteryLooper();
    void OnBatteryClick();
    void closeEvent(QCloseEvent * e) override;
    
    void initCoordModel();
    
    
public slots:
    void Arm(int v_id, bool value);
    void SetWayPoint(int v_id, int lat, int lng, int alt=0);
    
        void PauseMission(int v_id);
        void ResumeMission(int v_id);
        void CancelMission(int v_id);
    
    void onBtnAddClicked();
    void onBtnRemoveClicked();
    
    void onSpeedValueChanged(int value);
    
    void onTimedUpdate();
    
    void OnLeftClicked();
    void OnRightClicked();
    void OnUpClicked();
    void OnDownClicked();
    void OnCloseClicked();
    void OnGoClicked();
    void OnStopClicked();
    //test
    void onArmDisarmClicked();
    //void autoClicked();
    void OnReleased();
    
private:
    
    QThread * vr_thread;
    VoiceRecognition * vr;
    
    bool mission_paused;
    int battery_array[10];
    UGVControl *husky;
    Ui::MainWindow widget;

    ros::NodeHandle nh;
    ros::Publisher pub_cmd_vel;
    ros::Subscriber sub_events;
    
    image_transport::Subscriber sub_img;
    image_transport::ImageTransport it;
    std::thread batteryLooper;
    double linear,
           angular,
           linear_scale,
           angular_scale;
    int numberOfBatteryDisp;
    int batteryList[10];
    
    QStandardItemModel * model;
    
    std::vector<UGVControl::Point> waypoints;
    
    double linear_speed;
    
    QVector<QPixmap> img_q;
    
    QTimer * update_timer;
    
    int battery;
    
    void TranslateAndPublish();
    void connectToUiAdapter();
    void initVR();
    
};

class DoubleValidatorDelegate : public QItemDelegate
{
public:
    DoubleValidatorDelegate(QObject * parent) : 
    QItemDelegate(parent) {};
    
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override
    {
        QLineEdit * line_edit = new QLineEdit(parent);
        line_edit->setValidator(new QDoubleValidator(-2000, 2000, 2, line_edit));
        return line_edit;
    }
    
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override
    {
        QLineEdit * line_edit = static_cast<QLineEdit*>(editor);
        double val = line_edit->text().toDouble();
        model->setData(index, val, Qt::DisplayRole);
    }
    
    
};

#endif /* _MAINWINDOW_H */
