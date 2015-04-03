/*
 * ImageSaturation.h
 *
 *  Created on: 18/08/2013
 *      Author: james
 */

#ifndef ImageSaturation_H_
#define ImageSaturation_H_

#include <opencv2/opencv.hpp>
#include "TTerminal.h"
#include "ReturnImage.h"

class ImageSaturation : public TTerminal<cv::Mat, ReturnImage, ImageSaturation> {
public:
	ImageSaturation(GPConfig *conf);
	virtual ~ImageSaturation();
	virtual void evaluate(ReturnData *out);


    static const string NAME;
};

#endif /* ImageSaturation_H_ */
