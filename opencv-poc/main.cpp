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

    int top = 0;
    for(;;)
    {

        int i = rand();

//        switch(rand()%3)
//        {
//            case 0:
//                ;
//
//        }

        //blur the image
        Mat blur = source_mat.clone();
        GaussianBlur( source_mat, blur, Size( rand()%45*2+1, rand()%45*2+1 ), 0, 0 );

        //Mat sobelx;
        //Sobel(blur, sobelx, CV_32F, 1, 0);

        //simple threshhold
        Mat img_bw = blur > rand()%255 ;
        output_mat =  img_bw;

        //overlay on the source
        Mat dst2;
        double alpha = 0.5; double beta;
        beta = ( 1.0 - alpha );
        addWeighted( source_mat, alpha, output_mat, beta, 0.0, dst2);

        //show test image
        testWindow.showImage(dst2);


        //output score
        Mat diff_mat;
        cv::compare(truth_mat, output_mat, diff_mat, cv::CMP_EQ);
        int score =  cv::countNonZero(diff_mat);
        if(score >= top)
        {
            cout << "score is "<< score << endl;
            top = score;
            //overlay on the source
            Mat leader_mat;
            addWeighted( truth_mat,0.5 ,cv::Scalar::all(255) - diff_mat, 0.5, 0.0, leader_mat);


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