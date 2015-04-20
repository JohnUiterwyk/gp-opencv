#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "OpenCVWindow.h"
#include "Stopwatch.h"
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <sstream>

using namespace std;
using namespace cv;

Mat source_mat, truth_mat, output_mat;
OpenCVWindow sourceWindow("Unprocessed Image",300,300);
OpenCVWindow truthWindow("Ground truth",300,300);
OpenCVWindow testWindow("Current Image",300,300);
OpenCVWindow leaderWindow("Leader Image",300,300);
OpenCVWindow leaderDiffWindow("Leader Diff",300,300);

int main( int argc, char** argv )
{
    //timer code:
//    double readTime = (double)getTickCount();
//    readTime = ((double)getTickCount() - readTime)/getTickFrequency();

    /// Load the source image
    source_mat = cv::imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    truth_mat = cv::imread( argv[2], CV_LOAD_IMAGE_GRAYSCALE  );



    //create a window and add the image
    truthWindow.setPosition(source_mat.cols,0);
    testWindow.setPosition(source_mat.cols*2,0);
    leaderWindow.setPosition(source_mat.cols*3,0);
    leaderDiffWindow.setPosition(source_mat.cols*4,0);

    //hsv test
//    try {
//
//        Mat img=cv::imread(argv[1], CV_LOAD_IMAGE_COLOR);
//        Mat img2;
//
//        img.convertTo(img2, CV_32F);
//
//        cv::cvtColor(img2, img, CV_BGR2HSV);
//
//        vector<Mat> channels(3);
//        cv::split(img, channels);
//
//        sourceWindow.showImage(channels[0]);
//        testWindow.showImage(channels[1]);
//        leaderWindow.showImage(channels[2]);
//        waitKey(0);
//
//    }catch(int e)
//    {
//            cout << "error: " << e << endl;
//    }


    //end hsv test

    sourceWindow.showImage(source_mat);
    truthWindow.showImage(truth_mat);


    //Setup stopwatch
    Stopwatch appTimer(true);
    Stopwatch searchTimer(true);

    double best = 101;
    int size = 90000;
    int count = 0;
    int maxDepth = 5;
    for(;;)
    {
        count++;
        Mat input = source_mat;
        Mat output = source_mat.clone();
        int depth = rand()%maxDepth+1;
        int function = 0;
        int rand1 = 0;
        int rand2 = 0;
        ostringstream log;;

        for(int i= 0;i<depth;i++) {
            Mat working;
            function = rand();
            rand1 = rand();
            rand2 = rand();

            switch (function%4) {
                case 0:
                    log << "Gaussian("<< rand1 % 100 * 2 + 1 << ","<< rand2 % 100 * 2 + 1 <<"); ";
                    cv::GaussianBlur(input, working, Size(rand1 % 100 * 2 + 1, rand2 % 100 * 2 + 1), 0, 0);
                    output = working;
                    break;
                case 1:
                    log << "Sobel("<< rand1%2+1 << ","<< rand2%3 <<"); ";
                    cv::Sobel(input, working, CV_8U, rand1%2+1, rand2%3);
                    output = working;
                    break;
                case 2:
                    log << "Threshold("<< (rand1 % 128) <<"); ";
                    working = input > rand1 % 128;
                    output = working;
                    break;
                case 3:
                    log << "Bilateral("<< (rand1%300) <<","<<(rand2%300)<<"); ";
                    cv::bilateralFilter(input, working,5,(rand1%300),(rand2%300));
                    input = working;
                    convertScaleAbs( input, working );
                    output = working;
                    break;
                case 4:
                    log << "Laplacian(kernel_size="<< (rand1%3*2+1) <<"); ";
                    cv::Laplacian(input, working,CV_16S,rand1%15*2+1,1,0,BORDER_DEFAULT);
                    input = working;
                    convertScaleAbs( input, working );
                    output = working;
                    break;


            }
            input = output;
        }


        //one last threshold
        rand1 = rand();
        log << "Threshold("<< (rand1 % 255) <<"); ";
        Mat working;
        working = input > rand1 % 255;
        output = working;

//        //overlay on the source
        Mat dst2 = source_mat.clone();
        addWeighted( source_mat, 0.5, output, 0.5, 0.0, dst2);

        //show test image
        testWindow.showImage(output);



        //output score
        Mat diff_mat;
        cv::compare(truth_mat, output, diff_mat, cv::CMP_EQ);
        int nonzero = cv::countNonZero(diff_mat);
        double score = 100* (size - (double)nonzero)/size;
        if(score < best)
        {
            cout << fixed;
            cout << "### New Winner: ###" << endl;
            cout << "Error rate: "<< score << "%" <<endl;
            cout << "Functions: "<< log.str() << endl;
            cout << "Depth: "<< depth  << endl;
            best = score;
            //overlay on the source
            Mat leader_mat;
            addWeighted( truth_mat,0.5 ,output, 0.5, 0.0, leader_mat);

            cout << "Elapseds time: " << appTimer.GetTotalWallTime() << " seconds." << endl;
            cout << "Search time: " << searchTimer.GetTotalWallTime() << " seconds." << endl;
            cout << "FPS: " << count/appTimer.GetTotalWallTime() <<  endl;
            cout << "Count: " << count <<  endl;
            cout << endl;

            testWindow.showImage(output);
            leaderWindow.showImage(output);
            leaderDiffWindow.showImage(diff_mat);
            searchTimer.Stop();
            searchTimer.Start(true);
        };


        //create second window and output result
       if( waitKey(16) != -1)
           break;
    }

    waitKey(0);

    //stop runtime timer
    cout << "Total time: " << appTimer.GetTotalWallTime() << endl;

    //cout << "Tick frequency "<< std::fixed  << getTickFrequency() <<endl;



    //wait for user to press a key
    return 0;
}