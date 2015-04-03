#ifndef _RETURNUNIT_H_
#define _RETURNUNIT_H_


#include "ReturnData.h"

class ReturnUnit : public ReturnData
{
   private:
      double data; //The data for this class 

      /***********************************************
       This method sets the typeNum to be the typeid
       of the class.
      ************************************************/
      virtual void initTypeNum();

   public:
      static const int TYPENUM;

      ReturnUnit();
      virtual ~ReturnUnit();

      /************************
       Set the data to be num
      ************************/
      void setData(double num);
     
      /****************************
       Get the data of this class 
      ****************************/
      double getData() const;
     
   protected:

};

#endif
