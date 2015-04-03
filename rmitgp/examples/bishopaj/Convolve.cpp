
#include <string>

using namespace std;

#include "Convolve.h"
#include "ReturnKernel.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "CVDebug.h"


const string Convolve::NAME = "cv";

Convolve::Convolve(GPConfig *conf) : TFunction(conf, 2)
{
      setArgNReturnType(0, ReturnImage::TYPENUM);   
      setArgNReturnType(1, ReturnKernel::TYPENUM);   
}

Convolve::~Convolve()
{
}


void Convolve::evaluate_impl(ReturnData *out)
{

   ReturnImage src;
   ReturnKernel kernel;

   getArgN(0)->evaluate(&src);
   getArgN(1)->evaluate(&kernel);

   Mat result;

   cv::filter2D(src.getData(), result, -1, kernel.getData(), Point( -1, -1 ), 0, BORDER_DEFAULT);

	//CVDebug::logImage("Convolve", result);

   dynamic_cast<ReturnImage *>(out)->setData(result);
}



