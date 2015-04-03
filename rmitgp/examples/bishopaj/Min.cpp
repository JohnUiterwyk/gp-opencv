
#include <string>

using namespace std;

#include "Min.h"
#include "ReturnImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



const string Min::NAME = "min";

Min::Min(GPConfig *conf) : TFunction(conf, 1)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);
}

Min::~Min()
{
}


void Min::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   double val;
   cv::minMaxLoc(src.getData(), &val, NULL, NULL, NULL);


   dynamic_cast<ReturnDouble *>(out)->setData(val);
}



