#ifndef _Stdev_H_
#define _Stdev_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnDouble.h"

class Stdev : public TFunction<Stdev, ReturnDouble>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Stdev(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Stdev();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
