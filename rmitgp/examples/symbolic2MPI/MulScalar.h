#ifndef _MulScalar_H_
#define _MulScalar_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnImage.h"

class MulScalar : public TFunction<MulScalar, ReturnImage>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      MulScalar(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~MulScalar();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
