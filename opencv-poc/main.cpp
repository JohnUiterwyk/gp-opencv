#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

using namespace std;
using namespace cv;

Mat source_mat; Mat output_mat;
char window_name1[] = "Unprocessed Image";
char window_name2[] = "Processed Image";

int main( int argc, char** argv )
{

    //create a window and add the image
    namedWindow( window_name1, WINDOW_AUTOSIZE );
    moveWindow(window_name1,0,0);

    /// Load the source image
    clock_t startReadTime = clock();
    source_mat = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );
    cout << "Read time: " << double( clock() - startReadTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;

    imshow(window_name1,source_mat);

    //start runtime timer
    clock_t startTime = clock();

    //blur the image
    Mat blur = source_mat.clone();
    GaussianBlur( source_mat, blur, Size( 45, 45 ), 0, 0 );

    //Mat sobelx;
    //Sobel(blur, sobelx, CV_32F, 1, 0);

    //simple threshhold
    Mat img_bw = blur > 180 ;
    output_mat =  cv::Scalar::all(255) - img_bw;

    //overlay on the source
    Mat dst2;
    double alpha = 0.5; double beta;
    beta = ( 1.0 - alpha );
    addWeighted( source_mat, alpha, output_mat, beta, 0.0, dst2);

    //stop runtime timer
    cout << "filter time: " << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;

    //create second window and output result
    namedWindow( window_name2, WINDOW_AUTOSIZE );
    imshow(window_name2,dst2);
    moveWindow(window_name2,source_mat.cols,0);

    //wait for user to press a key
    waitKey();
    return 0;
}