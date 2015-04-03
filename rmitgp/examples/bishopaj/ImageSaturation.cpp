/*
 * ImageSaturation.cpp
 *
 *  Created on: 18/08/2013
 *      Author: james
 */

#include "ImageSaturation.h"
#include "CVDebug.h"

const string ImageSaturation::NAME = "S";

ImageSaturation::ImageSaturation(GPConfig *conf) : TTerminal(conf) {
	// TODO Auto-generated constructor stub

}

ImageSaturation::~ImageSaturation() {
	// TODO Auto-generated destructor stub
}

void ImageSaturation::evaluate(ReturnData *out)
{
	TTerminal<cv::Mat, ReturnImage, ImageSaturation>::evaluate(out);

	//CVDebug::logImage("ImageSaturation", this->value);

}
