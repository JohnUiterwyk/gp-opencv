/*
 * Kernel3x3.cpp
 *
 *  Created on: 19/08/2013
 *      Author: james
 */

#include "Kernel3x3.h"
#include <opencv2/opencv.hpp>
using namespace cv;
const string Kernel3x3::NAME = "K3";

#include "CVDebug.h"

Kernel3x3::Kernel3x3(GPConfig* conf) : TFunction(conf, 9) {

	for(int i=0;i<9;i++)
		setArgNReturnType(i, ReturnDouble::TYPENUM);
}

Kernel3x3::~Kernel3x3() {
	// TODO Auto-generated destructor stub
}

void Kernel3x3::evaluate_impl(ReturnData *out)
{
	Mat_<float> result(3,3);

	for(int i=0;i<9;i++)
	{
		ReturnDouble val;
		getArgN(i)->evaluate((ReturnData*)&val);

		result(i/3,i%3)=val.getData();
	}

	//CVDebug::logImage("Kernel3x3", result);


	   dynamic_cast<ReturnKernel *>(out)->setData(result);

}
