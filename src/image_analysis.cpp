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


Mat pathDetection(Mat frame){

    // Mat preparation for countours
    Mat frame_gray(frame.size(), CV_8UC1), frame_opened;
    cvtColor(frame, frame_gray, CV_RGB2GRAY);
    medianBlur ( frame_gray, frame_gray, 9 );
    threshold(frame_gray, frame_gray, 150, 255, CV_THRESH_BINARY);
    erode(frame_gray, frame_opened, getStructuringElement(MORPH_RECT, Size(8, 8)));
    dilate(frame_opened, frame_opened, getStructuringElement(MORPH_RECT, Size(50, 60)));
    
    // Find countours
    vector<vector<Point> > contours;
    vector<Vec4i> hierarchy;
    RNG rng(12345);
    findContours( frame_opened, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );

    /// Get rotated rectangle that best fits the countours
    vector<RotatedRect> minRect( contours.size() );

    for( int i = 0; i < contours.size(); i++ )
     { 
        minRect[i] = minAreaRect( Mat(contours[i]) );
     }
    
    /// Draw countours + rotated rectangle 
    Mat drawing = Mat::zeros( frame_opened.size(), CV_8UC3 );

    for( int i = 0; i< contours.size(); i++ )
    {
        Scalar white = Scalar( 255,255,255 );
        Scalar red = Scalar( 0,0,255 );
        // countours
        drawContours( drawing, contours, i, white, 2, 8, hierarchy, 0, Point() );
        // rotated rectangle
        Point2f rect_points[4]; minRect[i].points( rect_points );
        for( int j = 0; j < 4; j++ )
        {
            line( drawing, rect_points[j], rect_points[(j+1)%4], red, 2, 8 );
        }
    } 

    // Draw directional line 
    Mat line;
    vector<Point> cnt = contours.at(0);
    int rows =drawing.rows, cols = drawing.cols;
    fitLine(cnt,line, CV_DIST_L2,0,0.01,0.01);
    float vx = line.at<float>(0,0),vy = line.at<float>(1,0), x = line.at<float>(2,0), y = line.at<float>(3,0);
    float lefty = int((-x*vy/vx) + y);
    float righty = int(((cols-x)*vy/vx)+y);
    Scalar green = Scalar( 0,255,0 );
    cv::line(drawing,Point(cols-1,righty),Point(0,lefty),green,2,8);

    return drawing; 
}



int main(int argc, char **argv){

    Mat Image = cv::imread(argv[1], 1); //loads color if it is available
    Mat PathImage = pathDetection(Image);
    imshow("Contours",PathImage);

    waitKey(0);
    
    return 0;
}