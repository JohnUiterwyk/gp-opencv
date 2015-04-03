/*
 * ImageCase.h
 *
 *  Created on: 19/08/2013
 *      Author: james
 */

#ifndef ImageCase_H_
#define ImageCase_H_


#include <string>
#include <opencv2/opencv.hpp>

class ImageCase
{
public:

	cv::Mat brightness;
	cv::Mat saturation;
	cv::Mat hue;
	std::string filename;
	double result;
};



#endif /* ImageCase_H_ */
