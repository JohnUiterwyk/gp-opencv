
#include <string>

using namespace std;

#include "Mean.h"
#include "ReturnImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



const string Mean::NAME = "m";

Mean::Mean(GPConfig *conf) : TFunction(conf, 1)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);
}

Mean::~Mean()
{
}


void Mean::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   Scalar result;

   result=cv::mean(src.getData());


   dynamic_cast<ReturnDouble *>(out)->setData(result.val[0]);
}



