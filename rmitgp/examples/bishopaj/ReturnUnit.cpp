
#include "ReturnUnit.h"
#include <opencv2/opencv.hpp>
#include <string>
using namespace std;
using namespace cv;

//Initialise static data

const int ReturnUnit::TYPENUM=3;

ReturnUnit::ReturnUnit() : ReturnData(), data(0.0)
{
	initTypeNum();
}

ReturnUnit::~ReturnUnit()
{
}

void ReturnUnit::initTypeNum()
{
   setTypeNum(ReturnUnit::TYPENUM);
}

void ReturnUnit::setData(double num)
{
//	if(num<0 || num>1)
//		throw "Value outside unit interval";

   data = num;
   if(data>1)
	   data=1;
   else if(data<0)
	   data=0;
}

double ReturnUnit::getData() const
{
   return data;
}
