/*
 * Kernel3x3.h
 *
 *  Created on: 19/08/2013
 *      Author: james
 */

#ifndef KERNEL3X3_H_
#define KERNEL3X3_H_


#include "TFunction.h"
#include "ReturnKernel.h"
#include "ReturnDouble.h"
class GPConfig;

class Kernel3x3 : public TFunction<Kernel3x3, ReturnKernel>
{
public:
	Kernel3x3(GPConfig* conf);
	virtual ~Kernel3x3();
    static const string NAME;

protected:
	virtual void evaluate_impl(ReturnData *out);


};



#endif /* KERNEL3X3_H_ */
