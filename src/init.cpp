#include <stdlib.h>
#include <iostream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"

using namespace std;

void Initialize(Mat frame){

	/*

	// width and length
	w = frame.cols;
	l = frame.rows;

	// Color treatment
	Mat frame_gray(frame.size(), CV_8UC1);
    cvtColor(frame, frame_gray, CV_RGB2GRAY);
    medianBlur ( frame_gray, frame_gray, 9 );
    threshold(frame_gray, frame_gray, 150, 255, CV_THRESH_BINARY);

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
    imshow(",,",drawing); */
}

int main(int argc, char **argv){

	std::cout << "### Initialisation ###" << std::endl;

	Mat Image = cv::imread(argv[1], 1); //loads color if it is available
	if (Image.empty()) {
        std::cerr << "Error opening image" << std::endl;
        exit(EXIT_FAILURE);
    }

    int width, length, centerOfLine;
    Initialize(Image);
    // , width, length, centerOfLine
	return 0;
}