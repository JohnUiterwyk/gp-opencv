/******************************************************************************
 Definition file
 Class:        RandUnit
 Date created: 21/03/2002
 Written by:   Dylan Mawhinney

 See header file for details. 
***************************************************************************/

#include <cstdio> //for sprintf
#include <string>

using namespace std;

#include "GPConfig.h"

#include "RandUnit.h"
#include "ReturnDouble.h"
const string RandUnit::NAME = "ru";

RandUnit::RandUnit(GPConfig *conf) : TTerminalNonStatic(conf)
{
	value=config->randomNumGenerator->randReal();
}

RandUnit::RandUnit(double initValue, GPConfig *conf) : TTerminalNonStatic(conf,initValue)
{
}

RandUnit::~RandUnit()
{
}

void RandUnit::parse(const string &name)
{
	sscanf(name.c_str(), (RandUnit::NAME + "%lf").c_str(), &value);
}

void RandUnit::print(string &s)
{
	   char str[100];

	   sprintf(str, "%s%f", getName().c_str(), value);
	   s.append(str);
}

