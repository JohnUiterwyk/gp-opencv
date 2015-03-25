/*
 * CVDebug.h
 *
 *  Created on: 19/08/2013
 *      Author: james
 */

#ifndef CVDEBUG_H_
#define CVDEBUG_H_

#include <opencv2/opencv.hpp>
#include <iostream>
using namespace cv;

class CVDebug {
public:
	CVDebug();
	virtual ~CVDebug();

	static void init();
	static string logImage(string op, Mat img);
	static void setIndex(int i);
	static void incrementIndex();
	static void setEnabled(bool e);

	static int index;
	static int op_index;
	static bool enabled;
	static std::ofstream logstream;
};

#endif /* CVDEBUG_H_ */
