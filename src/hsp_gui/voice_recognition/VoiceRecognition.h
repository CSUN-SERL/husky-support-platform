/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   VoiceRecognition.h
 * Author: borhan
 *
 * Created on November 29, 2016, 8:16 PM
 */

#ifndef VOICERECOGNITION_H
#define VOICERECOGNITION_H

#include <QObject>
#include <QTimer>
#include <ros/package.h>

class VoiceRecognition : public QObject {
    Q_OBJECT
    public:
    VoiceRecognition();
    virtual ~VoiceRecognition();
    
public slots:
        void run();
        
private:
    bool quit = false;
    bool started = false;
    QTimer * timer;
};

#endif /* VOICERECOGNITION_H */

