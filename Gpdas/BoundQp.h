/*
 * BoundQp.h
 *
 *  Created on: Feb 21, 2012
 *      Author: zheng
 */

#ifndef BOUNDQP_H_
#define BOUNDQP_H_

// Structure for Bound QP problem:
// min 0.5x'Hx + c'x
// s.t    l<=x<=u

#include <iostream>
#include <vector>
#include "../DataStructure/BoundQpData.h"
#include "../DataStructure/GVars.h"
//#include "Algorithm/CallCplex.h"
//class GMatrix;
//class GVector;

class BoundQp:public BoundQpData{
public:
	// Constructors
	BoundQp(BoundQpData& BqpData);
	BoundQp(int n):BoundQpData(n)
		{x=new GVars(n,0.0);
		zl=new GVars(n,0.0);
		zu=new GVars(n,0.0);};
	BoundQp(GMatrix& H_,GVector& c_,GVector& l_,GVector& u_):
		BoundQpData(H_,c_,l_,u_)
		{x=new GVars(H_.size,0.0);
		zl=new GVars(H_.size,0.0);
		zu=new GVars(H_.size,0.0);};
	// Destructor
	virtual ~BoundQp(){};

	// Variables
	GVars* x;
	GVars* zl;
	GVars* zu;

	// Index sets
	vector<int> L;
	vector<int> U;
	vector<int> I;

	// Solver(s)
	void optimize();

	// For Pdas: update partition
	void update_partition();
	// For Pdas: update variables
	void update_vars();

	// Check optimality
	bool is_optimal();
	// Print out current iteration
	void print();

};




#endif /* BOUNDQP_H_ */
