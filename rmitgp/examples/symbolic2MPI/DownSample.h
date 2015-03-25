#ifndef _DownSample_H_
#define _DownSample_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnImage.h"

class DownSample : public TFunction<DownSample, ReturnImage>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      DownSample(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~DownSample();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
