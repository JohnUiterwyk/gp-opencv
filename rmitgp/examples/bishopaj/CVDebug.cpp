/*
 * CVDebug.cpp
 *
 *  Created on: 19/08/2013
 *      Author: james
 */

#include "CVDebug.h"
#include <sstream>
#include <iostream>
#include <fstream>

using namespace std;

string CVDebug::logImage(string op, Mat img)
{
	string fname="";
	if(enabled)
	{
		stringstream sstr;
		sstr << "cvdbg_" << index << "_" << op_index << "_" << op << ".jpg";
		fname=sstr.str();

		Mat tmp = img * 255;

		//float min=*std::min_element(img.begin<float>(), img.end<float>());
		//float max=*std::max_element(img.begin<float>(), img.end<float>());

		cv::imwrite(fname, tmp);
	}
	op_index++;
	return fname;
}
void CVDebug::setIndex(int i)
{
	index=i;
	op_index=0;
}

void CVDebug::incrementIndex()
{
	setIndex(index+1);
}
void CVDebug::setEnabled(bool e)
{
	if(e && !enabled)
	{
		logstream.close();
		logstream.open("cvdebug.log");
	}
	else if(!e && enabled)
	{
		logstream.close();
		logstream.open("/dev/null");
	}

	enabled=e;

}

void CVDebug::init()
{
	setIndex(0);
	setEnabled(false);
}

int CVDebug::index=0;
int CVDebug::op_index=0;
bool CVDebug::enabled=false;
std::ofstream CVDebug::logstream;

CVDebug::CVDebug() {
	// TODO Auto-generated constructor stub

}

CVDebug::~CVDebug() {
	// TODO Auto-generated destructor stub
}

