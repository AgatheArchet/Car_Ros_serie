#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
//#include "opencv2/imgcodecs.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "imgUtils.h"
#include <iostream>
#include <stdlib.h>
#include <list>
#include <limits>
#include <math.h>


using namespace std;

/*
The process is :
*Capture an image
*Define the ROI
*Identify all of the black regions in this ROI
*Select the left most or right most edge of the corresponding region
*Offset this point to centre the tracking point
*Calculate the steering signal based on how far the tracking point is from the centre of the ROI

*/

/*

Mat video(VideoCapture cap){
    if(!cap.open(0)){
        cout << "Error opening video stream or file" << endl;
        break;
    }
    int frame_width = cap.get(CV_CAP_PROP_FRAME_WIDTH);
    int frame_height = cap.get(CV_CAP_PROP_FRAME_HEIGHT);
    //VideoWriter video("../images/webcam.avi",CV_FOURCC('M','J','P','G'),10, Size(frame_width,frame_height),true);
    Mat frame;
    cap >> frame;
    if (frame.empty())
      break;
    return frame;
} */

float getMidPoint(int bias, Mat camImage)
{   
    //video(VideoCapture cap);
    Rect region_of_interest = Rect(10, 2*camImage.rows/3, camImage.cols-20, camImage.rows/12);
    Mat roi = camImage(region_of_interest);
    Mat mono;
    cvtColor(roi, mono, COLOR_RGB2GRAY);
    Mat blur;
    GaussianBlur(mono, blur, Size(9, 9), 2, 2);
    Mat thresh;
    threshold(blur, thresh, 0, 255, THRESH_BINARY_INV|THRESH_OTSU);
    Mat dilateImg;
    dilate(thresh, dilateImg, getStructuringElement(MORPH_RECT, Size(5, 5)));
    Mat erodeImg;
    erode(dilateImg, erodeImg, getStructuringElement(MORPH_RECT, Size(5, 5)));
    vector<vector<Point> > contours;
    vector<Vec4i> notused;
    findContours(erodeImg, contours, notused, RETR_LIST, CHAIN_APPROX_SIMPLE);
    double minMaxCx = (bias > 0 ? -std::numeric_limits<double>::infinity() : std::numeric_limits<double>::infinity());
    for(int i = 0; i< contours.size(); i++ )
    {
        Moments mu = moments(contours, false);
        if (mu.m00 > 100.0)
        {
            Rect r = boundingRect(contours);
            double cx;
            if (bias > 0)
            {
                cx = r.x + r.width - 12;
                if (cx > minMaxCx)
                {
                    minMaxCx = cx;
                }
            }
            else
            {
                cx = r.x + 12;
                if (minMaxCx > cx)
                {
                    minMaxCx = cx;
                }
            }
        }
    }
    if (isinf(minMaxCx))
        minMaxCx = roi.cols/2;
    
    return 1.0f - 2.0f*(float)minMaxCx/roi.cols;
}




int main(int argc, char **argv){

    Mat I = imgUtils::readImage(argc, argv);
    float midpoint = getMidPoint(0, I);
    cout << midpoint << endl;
    
    return 0;
}