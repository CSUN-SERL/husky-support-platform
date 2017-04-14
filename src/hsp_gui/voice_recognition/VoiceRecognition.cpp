/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/*
 * File:   VoiceRecognition.cpp
 * Author: borhan
 *
 * Created on November 29, 2016, 8:16 PM
 */

#include <voice_recognition/VoiceRecognition.h>
#include <voice_recognition/CommandParser.h>
#include <iostream>
#include <voce/voce.h>
#include <boost/algorithm/string.hpp>
#include <QTimer>
#include <QThread>

VoiceRecognition::VoiceRecognition() {


//    timer = new QTimer(this);
//    connect(timer, &QTimer::timeout, this, &VoiceRecognition::run);
//    timer->start(40);

}


VoiceRecognition::~VoiceRecognition() {
    voce::destroy();
}

void VoiceRecognition::run()
{
    std::string path = ros::package::getPath("voice_recognition");
    path.append("/resources");
    std::cout << path << std::endl;

    voce::init("/opt/voce/lib", false, true, path, "islurp");

    std::cout << "Voice initialize" << std::endl;


    std::cout << "running" << std::endl;
    while (!quit)
    {
        // Normally, applications would do application-specific things
        // here.  For this sample, we'll just sleep for a little bit.

        while (voce::getRecognizerQueueSize() > 0)
        {
            std::string s = voce::popRecognizedString();

            // Check if the string contains 'quit'.
            if (std::string::npos != s.rfind("quit"))
            {
                quit = true;
                this->thread()->requestInterruption();
                return;
            }
            if (s == "end voice")
            {
                started = false;
                std::cout << "Voice Recognition stopped!"<< std::endl;
                break;
            }
            else if (s == "start")
            {
                std::cout << "Voice Recognition started!"<< std::endl;
                started = true;
            }
            else if (started)
            {
                 boost::to_upper(s);

                 std::cout << "TEST: " << s << std::endl;

                 CommandParser p;
                 p.parse(s);


                std::cout << "You said ----------: " << s << std::endl;


            //voce::synthesize(s);

            } // else if (started)

        }//while (voce::getRecognizerQueueSize() > 0

        // QCoreApplication::processEvents();

      }  //while(!quit)

}
