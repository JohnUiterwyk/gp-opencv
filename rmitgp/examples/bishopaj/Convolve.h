#ifndef _Convolve_H_
#define _Convolve_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnImage.h"

class Convolve : public TFunction<Convolve, ReturnImage>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Convolve(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Convolve();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
