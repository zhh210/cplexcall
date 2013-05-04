/*
 * GVars.h
 *
 *  Created on: Feb 21, 2012
 *      Author: zheng
 */

#ifndef GVARS_H_
#define GVARS_H_

#include "GVector.h"

class GVars:public GVector{
public:
	// Constructors
	GVars();
	GVars(int n):GVector(n){};
	GVars(int n,double val):GVector(n,val){};

private:
};

#endif /* GVARS_H_ */
