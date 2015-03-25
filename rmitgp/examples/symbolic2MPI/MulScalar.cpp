
#include <string>

using namespace std;

#include "MulScalar.h"
#include "ReturnKernel.h"
#include "ReturnDouble.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "CVDebug.h"


const string MulScalar::NAME = "ms";

MulScalar::MulScalar(GPConfig *conf) : TFunction(conf, 2)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
}

MulScalar::~MulScalar()
{
}


void MulScalar::evaluate_impl(ReturnData *out)
{

   ReturnImage src;
   ReturnDouble value;

   getArgN(0)->evaluate(&src);
   getArgN(1)->evaluate(&value);

   Mat result;

   result = src.getData() * value.getData();

   dynamic_cast<ReturnImage *>(out)->setData(result);
}



