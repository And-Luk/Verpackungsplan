//
//  photo.cpp
//  Verpackungsplan
//
//  Created by Andrei Lukashevich on 08-10-2025.
//
#include "photo.h"

using namespace cv;


int take_a_photo(){
    
    std::string Screenshot_name{"./Pictures/"};
    std::time_t rawtime;
    std::tm* timeinfo;
    char buffer [80];

    std::time(&rawtime);
    timeinfo = std::localtime(&rawtime);
    std::strftime(buffer,80,"%Y-%m-%d_%H:%M:%S",timeinfo);   //%Y-%m-%d-%H-%M-%S    %d-%m-%Y    %H:%M:%S
       
    Screenshot_name.append(buffer);
    Screenshot_name.append(".jpg");

    // open the first webcam plugged in the computer
       cv::VideoCapture camera(0); // in linux check $ ls /dev/video0
       if (!camera.isOpened()) {
           std::cerr << "ERROR: Could not open camera" << std::endl;
           return 1;
       }

       // create a window to display the images from the webcam
       cv::namedWindow("Webcam", cv::WINDOW_AUTOSIZE);

       // array to hold image
    cv::Mat image;
           camera >> image;

           cv::imwrite(Screenshot_name.c_str(), image);
           cv::destroyAllWindows();

           return 0;
}


