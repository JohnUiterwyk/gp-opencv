#ifndef _RANDUNIT_H_
#define _RANDUNIT_H_


class GPConfig;

#include <string>
#include "TTerminal.h"
#include "ReturnUnit.h"


class RandUnit: public TTerminalNonStatic<double, ReturnUnit, RandUnit>
{

   public:
      RandUnit(GPConfig *conf);
      explicit RandUnit(double initValue, GPConfig *conf);
      virtual ~RandUnit();

      virtual void print(string &s);
      virtual void parse(const string &name);
      static const string NAME;

   protected:

};



#endif
