
#include <string>

using namespace std;

#include "Crop.h"
#include "ReturnDouble.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "CVDebug.h"

const string Crop::NAME = "cr";

Crop::Crop(GPConfig *conf) : TFunction(conf, 5)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
    setArgNReturnType(2, ReturnDouble::TYPENUM);
    setArgNReturnType(3, ReturnDouble::TYPENUM);
    setArgNReturnType(4, ReturnDouble::TYPENUM);
}

Crop::~Crop()
{
}


void Crop::evaluate_impl(ReturnData *out)
{

   ReturnImage src;

   getArgN(0)->evaluate(&src);

   ReturnDouble minx, miny, maxx, maxy;
   getArgN(1)->evaluate(&minx);
   getArgN(2)->evaluate(&miny);
   getArgN(3)->evaluate(&maxx);
   getArgN(4)->evaluate(&maxy);




   Mat img=src.getData();

   int rminx = (int)(MIN(MAX(minx.getData(),0.0),1.0) * img.cols);
   int rminy = (int)(MIN(MAX(miny.getData(),0.0),1.0) * img.rows);
   int rmaxx = (int)(MIN(MAX(maxx.getData(),0.0),1.0) * img.cols);
   int rmaxy = (int)(MIN(MAX(maxy.getData(),0.0),1.0) * img.rows);

   if(rminx>rmaxx)
      swap(rminx, rmaxx);
   if(rminy>rmaxy)
	   swap(rminy, rmaxy);

  cv::Rect roi(rminx, rminy, rmaxx-rminx, rmaxy-rminy);

   Mat result = img(roi);


	//CVDebug::logImage("Crop", result);

   dynamic_cast<ReturnImage *>(out)->setData(result);
}



