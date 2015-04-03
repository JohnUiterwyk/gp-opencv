/*
 * ImageHue.cpp
 *
 *  Created on: 18/08/2013
 *      Author: james
 */

#include "ImageHue.h"
#include "CVDebug.h"

const string ImageHue::NAME = "H";

ImageHue::ImageHue(GPConfig *conf) : TTerminal(conf) {
	// TODO Auto-generated constructor stub

}

ImageHue::~ImageHue() {
	// TODO Auto-generated destructor stub
}

void ImageHue::evaluate(ReturnData *out)
{
	TTerminal<cv::Mat, ReturnImage, ImageHue>::evaluate(out);

	//CVDebug::logImage("ImageHue", this->value);

}
