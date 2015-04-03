
#include "ReturnMat.h"

//Initialise static data

ReturnMat::ReturnMat()
{
	data = Mat::zeros(1, 1, CV_32F);
}

ReturnMat::~ReturnMat()
{
}

