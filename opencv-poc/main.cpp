#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OpenCVWindow.h"
#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;
using namespace cv;

Mat source_mat, truth_mat, output_mat;
OpenCVWindow sourceWindow("Unprocessed Image",300,300);
OpenCVWindow testWindow("Current Image",300,300);
OpenCVWindow leaderWindow("Leader Image",300,300);

int main( int argc, char** argv )
{
    //timer code:
//    double readTime = (double)getTickCount();
//    readTime = ((double)getTickCount() - readTime)/getTickFrequency();

    /// Load the source image
    source_mat = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    truth_mat = imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE );

    //create a window and add the image
    testWindow.setPosition(source_mat.cols,0);
    leaderWindow.setPosition(source_mat.cols*2,0);

    sourceWindow.showImage(source_mat);

    //start runtime timer
    double filterTime = (double)getTickCount();

    int top = 90000;
    for(;;)
    {
        Mat input = source_mat;
        Mat output = source_mat.clone();
        int depth = rand()%7+1;
        int function = 0;
        for(int i= 0;i<depth;i++) {
            Mat working;
            function = rand();
            switch (function%3) {
                case 0:
                    GaussianBlur(input, working, Size(rand() % 100 * 2 + 1, rand() % 100 * 2 + 1), 0, 0);
                    output = working;
                    break;
                case 1:
                    Sobel(input, working, CV_8U, rand()%2+1, rand()%3);
                    output = working;
                    break;
                case 2:
                    working = input > rand() % 255;
                    output = working;
                    break;


            }
            input = output;
        }
//        //overlay on the source
        Mat dst2 = source_mat.clone();
        addWeighted( source_mat, 0.5, output, 0.5, 0.0, dst2);

        //show test image
        testWindow.showImage(output);


        //output score
        Mat diff_mat;
        cv::compare(truth_mat, output, diff_mat, cv::CMP_NE);
        int score =  cv::countNonZero(diff_mat);
        if(score <= top)
        {
            cout << "errors: "<< score << " depth:"<< depth << " func:" << function%3 << endl;
            top = score;
            //overlay on the source
            Mat leader_mat;
            addWeighted( truth_mat,0.5 ,output, 0.5, 0.0, leader_mat);


            leaderWindow.showImage(leader_mat);
        }


        //create second window and output result
       if( waitKey(16) != -1)
           break;
    }


    //stop runtime timer
    filterTime = ((double)getTickCount() - filterTime)/getTickFrequency();
    cout << "Filter time: " << filterTime << " seconds." << endl;

    //cout << "Tick frequency "<< std::fixed  << getTickFrequency() <<endl;



    //wait for user to press a key
    return 0;
}