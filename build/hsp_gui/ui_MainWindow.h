/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionDem_titties;
    QAction *actionFile;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *Go_Button;
    QSlider *horizontalSlider;
    QLabel *image_frame;
    QPushButton *stop_Button;
    QProgressBar *batteryBar;
    QPushButton *close_button;
    QGridLayout *gridLayout_2;
    QPushButton *btn_down;
    QPushButton *btn_right;
    QPushButton *btn_left;
    QPushButton *btn_up;
    QGridLayout *gridLayout_3;
    QLineEdit *LatBox;
    QPushButton *loc_Button;
    QLineEdit *LongBox;
    QLabel *LatAndLong;
    QTextEdit *textEdit;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1059, 881);
        actionDem_titties = new QAction(MainWindow);
        actionDem_titties->setObjectName(QStringLiteral("actionDem_titties"));
        actionFile = new QAction(MainWindow);
        actionFile->setObjectName(QStringLiteral("actionFile"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QStringLiteral("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        Go_Button = new QPushButton(centralwidget);
        Go_Button->setObjectName(QStringLiteral("Go_Button"));
        Go_Button->setFocusPolicy(Qt::StrongFocus);
        Go_Button->setStyleSheet(QLatin1String("background-color: rgb(85, 170, 127);\n"
"font: 75 12pt \"STIX\";\n"
"color: rgb(0, 0, 0);"));
        Go_Button->setCheckable(true);
        Go_Button->setAutoRepeat(true);
        Go_Button->setAutoRepeatDelay(0);
        Go_Button->setAutoRepeatInterval(2);

        gridLayout->addWidget(Go_Button, 1, 2, 1, 1);

        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setFocusPolicy(Qt::StrongFocus);
        horizontalSlider->setOrientation(Qt::Horizontal);

        gridLayout->addWidget(horizontalSlider, 0, 2, 1, 1);

        image_frame = new QLabel(centralwidget);
        image_frame->setObjectName(QStringLiteral("image_frame"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(1);
        sizePolicy.setVerticalStretch(1);
        sizePolicy.setHeightForWidth(image_frame->sizePolicy().hasHeightForWidth());
        image_frame->setSizePolicy(sizePolicy);
        image_frame->setMinimumSize(QSize(100, 100));

        gridLayout->addWidget(image_frame, 4, 0, 1, 1);

        stop_Button = new QPushButton(centralwidget);
        stop_Button->setObjectName(QStringLiteral("stop_Button"));
        stop_Button->setFocusPolicy(Qt::StrongFocus);
        stop_Button->setStyleSheet(QLatin1String("background-color: rgb(255, 85, 0);\n"
"font: 75 12pt \"STIX\";"));

        gridLayout->addWidget(stop_Button, 3, 2, 1, 1);

        batteryBar = new QProgressBar(centralwidget);
        batteryBar->setObjectName(QStringLiteral("batteryBar"));
        QPalette palette;
        QBrush brush(QColor(0, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 255, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        QBrush brush2(QColor(127, 127, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush2);
        QBrush brush3(QColor(63, 63, 255, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Midlight, brush3);
        QBrush brush4(QColor(0, 0, 127, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Dark, brush4);
        QBrush brush5(QColor(0, 0, 170, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush6(QColor(255, 255, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush6);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Active, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Active, QPalette::AlternateBase, brush2);
        QBrush brush7(QColor(255, 255, 220, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Inactive, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush6);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush2);
        palette.setBrush(QPalette::Disabled, QPalette::Midlight, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Dark, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Mid, brush5);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush4);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        palette.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        batteryBar->setPalette(palette);
        batteryBar->setFocusPolicy(Qt::StrongFocus);
        batteryBar->setStyleSheet(QStringLiteral(""));
        batteryBar->setValue(69);
        batteryBar->setTextVisible(true);

        gridLayout->addWidget(batteryBar, 7, 0, 1, 1);

        close_button = new QPushButton(centralwidget);
        close_button->setObjectName(QStringLiteral("close_button"));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush6);
        QBrush brush8(QColor(170, 170, 255, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush8);
        QBrush brush9(QColor(255, 0, 0, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush9);
        QBrush brush10(QColor(212, 0, 0, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush10);
        QBrush brush11(QColor(85, 0, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush11);
        QBrush brush12(QColor(113, 0, 0, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush8);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush);
        QBrush brush13(QColor(212, 127, 127, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush11);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush13);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush11);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush12);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush);
        QBrush brush14(QColor(170, 0, 0, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush14);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush);
        close_button->setPalette(palette1);
        close_button->setFocusPolicy(Qt::StrongFocus);
        close_button->setAutoFillBackground(false);
        close_button->setStyleSheet(QLatin1String("color: rgb(255, 255, 255);\n"
"background-color: rgb(170, 170, 255);\n"
"font: 75 12pt \"STIX\";"));

        gridLayout->addWidget(close_button, 7, 2, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        btn_down = new QPushButton(centralwidget);
        btn_down->setObjectName(QStringLiteral("btn_down"));
        btn_down->setMaximumSize(QSize(40, 16777215));
        btn_down->setFocusPolicy(Qt::StrongFocus);
        btn_down->setCheckable(true);
        btn_down->setAutoRepeat(true);
        btn_down->setAutoRepeatDelay(0);
        btn_down->setAutoRepeatInterval(2);

        gridLayout_2->addWidget(btn_down, 3, 3, 1, 1, Qt::AlignTop);

        btn_right = new QPushButton(centralwidget);
        btn_right->setObjectName(QStringLiteral("btn_right"));
        btn_right->setMaximumSize(QSize(40, 16777215));
        btn_right->setCheckable(true);
        btn_right->setAutoRepeat(true);
        btn_right->setAutoRepeatDelay(0);
        btn_right->setAutoRepeatInterval(2);

        gridLayout_2->addWidget(btn_right, 3, 4, 1, 1, Qt::AlignLeft);

        btn_left = new QPushButton(centralwidget);
        btn_left->setObjectName(QStringLiteral("btn_left"));
        btn_left->setMaximumSize(QSize(40, 16777215));
        btn_left->setCheckable(true);
        btn_left->setAutoRepeat(true);
        btn_left->setAutoRepeatDelay(0);
        btn_left->setAutoRepeatInterval(2);

        gridLayout_2->addWidget(btn_left, 3, 2, 1, 1, Qt::AlignRight);

        btn_up = new QPushButton(centralwidget);
        btn_up->setObjectName(QStringLiteral("btn_up"));
        btn_up->setMaximumSize(QSize(40, 16777215));
        btn_up->setFocusPolicy(Qt::StrongFocus);
        btn_up->setCheckable(true);
        btn_up->setChecked(false);
        btn_up->setAutoRepeat(true);
        btn_up->setAutoRepeatDelay(0);
        btn_up->setAutoRepeatInterval(2);

        gridLayout_2->addWidget(btn_up, 2, 3, 1, 1, Qt::AlignBottom);


        gridLayout->addLayout(gridLayout_2, 5, 2, 2, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        LatBox = new QLineEdit(centralwidget);
        LatBox->setObjectName(QStringLiteral("LatBox"));
        LatBox->setFocusPolicy(Qt::StrongFocus);

        gridLayout_3->addWidget(LatBox, 1, 0, 1, 1);

        loc_Button = new QPushButton(centralwidget);
        loc_Button->setObjectName(QStringLiteral("loc_Button"));
        loc_Button->setFocusPolicy(Qt::StrongFocus);
        loc_Button->setStyleSheet(QLatin1String("background-color: rgb(0, 170, 255);\n"
"font: 75 12pt \"STIX\";"));

        gridLayout_3->addWidget(loc_Button, 2, 0, 1, 1);

        LongBox = new QLineEdit(centralwidget);
        LongBox->setObjectName(QStringLiteral("LongBox"));
        LongBox->setFocusPolicy(Qt::StrongFocus);

        gridLayout_3->addWidget(LongBox, 1, 1, 1, 1);

        LatAndLong = new QLabel(centralwidget);
        LatAndLong->setObjectName(QStringLiteral("LatAndLong"));
        LatAndLong->setStyleSheet(QStringLiteral("font: 12pt \"STIX\";"));

        gridLayout_3->addWidget(LatAndLong, 0, 0, 1, 1);


        gridLayout->addLayout(gridLayout_3, 1, 0, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName(QStringLiteral("textEdit"));
        textEdit->setFocusPolicy(Qt::StrongFocus);

        gridLayout->addWidget(textEdit, 4, 2, 1, 1);

        MainWindow->setCentralWidget(centralwidget);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "turtle_teleop_key_gui", 0));
        actionDem_titties->setText(QApplication::translate("MainWindow", "dem titties", 0));
        actionFile->setText(QApplication::translate("MainWindow", "\\", 0));
        Go_Button->setText(QApplication::translate("MainWindow", "GO!", 0));
        image_frame->setText(QString());
        stop_Button->setText(QApplication::translate("MainWindow", "STOP!!", 0));
        close_button->setText(QApplication::translate("MainWindow", "Close", 0));
        btn_down->setText(QApplication::translate("MainWindow", "v", 0));
        btn_right->setText(QApplication::translate("MainWindow", ">", 0));
        btn_left->setText(QApplication::translate("MainWindow", "<", 0));
        btn_up->setText(QApplication::translate("MainWindow", "^", 0));
        loc_Button->setText(QApplication::translate("MainWindow", "Update", 0));
        LatAndLong->setText(QApplication::translate("MainWindow", "Enter Lattitude and Longitude", 0));
        textEdit->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Ubuntu'; font-size:11pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Please Input the Coordinates!!</p></body></html>", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
