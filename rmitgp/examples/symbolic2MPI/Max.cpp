
#include <string>

using namespace std;

#include "Max.h"
#include "ReturnImage.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>



const string Max::NAME = "max";

Max::Max(GPConfig *conf) : TFunction(conf, 1)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);
}

Max::~Max()
{
}


void Max::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   double val;
   cv::minMaxLoc(src.getData(), NULL, &val, NULL, NULL);


   dynamic_cast<ReturnDouble *>(out)->setData(val);
}



