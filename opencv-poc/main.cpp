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

    /// Load the source image
    source_mat = imread( argv[1], CV_LOAD_IMAGE_GRAYSCALE );

    namedWindow( window_name1, WINDOW_AUTOSIZE );
    imshow(window_name1,source_mat);
    clock_t startTime = clock();
    Mat blur = source_mat.clone();
    GaussianBlur( source_mat, blur, Size( 45, 45 ), 0, 0 );


    Mat sobelx;
    Sobel(blur, sobelx, CV_32F, 1, 0);


//    Mat dst2;
//    double alpha = 0.5; double beta;
//    beta = ( 1.0 - alpha );
//    addWeighted( src, alpha, sobelx, beta, 0.0, dst2);


    Mat img_bw = sobelx > 20;
    output_mat =  cv::Scalar::all(255) - img_bw;

    cout << double( clock() - startTime ) / (double)CLOCKS_PER_SEC<< " seconds." << endl;


    namedWindow( window_name2, WINDOW_AUTOSIZE );
    imshow(window_name2,output_mat);
    moveWindow(window_name2,100,100);

    waitKey();
    return 0;
}