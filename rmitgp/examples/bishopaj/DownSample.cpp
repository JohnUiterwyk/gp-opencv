
#include <string>

using namespace std;

#include "DownSample.h"
#include "ReturnKernel.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "CVDebug.h"


const string DownSample::NAME = "ds";

DownSample::DownSample(GPConfig *conf) : TFunction(conf, 1)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);   
}

DownSample::~DownSample()
{
}


void DownSample::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   Mat srcimg = src.getData();

   if(srcimg.rows>1 && srcimg.cols>1)
   {
	   Mat result;

	   cv::resize(srcimg, result, Size(), 0.5, 0.5, INTER_LINEAR);

	   dynamic_cast<ReturnImage *>(out)->setData(result);
   }
   else
	   dynamic_cast<ReturnImage *>(out)->setData(srcimg);
}



