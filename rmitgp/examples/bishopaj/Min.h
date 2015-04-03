#ifndef _Min_H_
#define _Min_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnDouble.h"

class Min : public TFunction<Min, ReturnDouble>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Min(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Min();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
