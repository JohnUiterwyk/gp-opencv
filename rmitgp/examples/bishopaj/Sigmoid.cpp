
#include <string>

using namespace std;

#include "Sigmoid.h"
#include "ReturnKernel.h"
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "CVDebug.h"


const string Sigmoid::NAME = "sig";

Sigmoid::Sigmoid(GPConfig *conf) : TFunction(conf, 1)
{
    setArgNReturnType(0, ReturnDouble::TYPENUM);
}

Sigmoid::~Sigmoid()
{
}


void Sigmoid::evaluate_impl(ReturnData *out)
{

   ReturnDouble value;

   getArgN(0)->evaluate(&value);

   double result;

   result = 1 / (1 + exp( - value.getData()));

   dynamic_cast<ReturnDouble *>(out)->setData(result);
}



