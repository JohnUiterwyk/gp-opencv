
#include <string>

using namespace std;

#include "AddScalar.h"
#include "ReturnKernel.h"
#include "ReturnDouble.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "CVDebug.h"


const string AddScalar::NAME = "as";

AddScalar::AddScalar(GPConfig *conf) : TFunction(conf, 2)
{
    setArgNReturnType(0, ReturnImage::TYPENUM);
    setArgNReturnType(1, ReturnDouble::TYPENUM);
}

AddScalar::~AddScalar()
{
}


void AddScalar::evaluate_impl(ReturnData *out)
{

   ReturnImage src;
   ReturnDouble value;

   getArgN(0)->evaluate(&src);
   getArgN(1)->evaluate(&value);

   Mat result;

   result = src.getData() + value.getData();

   dynamic_cast<ReturnImage *>(out)->setData(result);
}



