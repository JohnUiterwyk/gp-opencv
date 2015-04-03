#ifndef _Max_H_
#define _Max_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnDouble.h"

class Max : public TFunction<Max, ReturnDouble>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Max(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Max();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
