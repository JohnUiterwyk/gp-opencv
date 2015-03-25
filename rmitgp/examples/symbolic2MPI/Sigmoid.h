#ifndef _Sigmoid_H_
#define _Sigmoid_H_


class GPConfig;

#include <string>
#include "TFunction.h"
#include "ReturnImage.h"
#include "ReturnDouble.h"

class Sigmoid : public TFunction<Sigmoid, ReturnDouble>
{
   private:

   public:
      /*************
       Constructor.
      **************/
      Sigmoid(GPConfig *conf);

      /*********************
       virtual destructor
      *********************/
      virtual ~Sigmoid();

      static const string NAME;

   protected:
   	virtual void evaluate_impl(ReturnData *out);

};


#endif
