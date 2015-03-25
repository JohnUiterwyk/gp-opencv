/*
 * ImageHue.h
 *
 *  Created on: 18/08/2013
 *      Author: james
 */

#ifndef ImageHue_H_
#define ImageHue_H_

#include <opencv2/opencv.hpp>
#include "TTerminal.h"
#include "ReturnImage.h"

class ImageHue : public TTerminal<cv::Mat, ReturnImage, ImageHue> {
public:
	ImageHue(GPConfig *conf);
	virtual ~ImageHue();
	virtual void evaluate(ReturnData *out);


    static const string NAME;
};

#endif /* ImageHue_H_ */
