#ifndef _ReturnMat_H_
#define _ReturnMat_H_

#include "ReturnValue.h"
#include <opencv2/opencv.hpp>
using namespace cv;


class ReturnMat : public ReturnValue<Mat, ReturnMat>
{
public:
      ReturnMat();
      virtual ~ReturnMat();
	  static const int TYPENUM=4;

};


#endif
