#ifndef _AddScalar_H_
#define _AddScalar_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnImage.h"

class AddScalar : public TFunction<AddScalar, ReturnImage>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      AddScalar(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~AddScalar();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
