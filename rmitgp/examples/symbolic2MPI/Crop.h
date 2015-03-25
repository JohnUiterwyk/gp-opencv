#ifndef _Crop_H_
#define _Crop_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnImage.h"

class Crop : public TFunction<Crop, ReturnImage>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Crop(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Crop();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
