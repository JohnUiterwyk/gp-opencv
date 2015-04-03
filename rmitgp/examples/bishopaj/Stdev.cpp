
#include <string>

using namespace std;

#include "Stdev.h"
#include "ReturnImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



const string Stdev::NAME = "std";

Stdev::Stdev(GPConfig *conf) : TFunction(conf, 1)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);
}

Stdev::~Stdev()
{
}


void Stdev::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   Scalar mean;
   Scalar stdev;

   cv::meanStdDev(src.getData(), mean, stdev);


   dynamic_cast<ReturnDouble *>(out)->setData(stdev.val[0]);
}



