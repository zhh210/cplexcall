/*
 * BoundQpData.h
 *
 *  Created on: Feb 21, 2012
 *      Author: zheng
 */

// A naive data structure for PDAS including:
// GMatrix: A matrix for storing Hessian;
// GVector: A vector for storing coefficient vector;
// GVars:   An array for storing variables;
// Bound QP problem:
// min 0.5x'Hx + c'x
// s.t    l<=x<=u

#ifndef BOUNDQPDATA_H_
#define BOUNDQPDATA_H_

#include <stdlib.h>
#include <stdio.h>
#include <ctime>

#include "GMatrix.h"
#include "GVector.h"
#include "GVars.h"


class BoundQpData{
protected:
	GMatrix * H; 		// Hessian
	GVector * c;		// Linear Coefficient
	GVector * l;		// Lower Bound
	GVector * u;		// Upper Bound
	int size;			// Problem Size

public:
	// Constructors
	BoundQpData(int n):size(n){};
	BoundQpData(GMatrix& H_,GVector& c_,GVector& l_,GVector& u_);
	// Printout Data
	friend ostream& operator<<(ostream& out, BoundQpData& Bqp);
	// Generate Random Data
	virtual void MakeRandomData();
	// Destructor
	virtual ~BoundQpData(){};

	int getsize(){return size;}
	GMatrix* getH(){return H;};
	GVector* getg(){return c;};
	GVector* getl(){return l;};
	GVector* getu(){return u;};
};



// Generate random data for the problem
void BoundQpData::MakeRandomData(){
	// Generate random PSD matrix as Hessian
	H = new GMatrix(size,0.0);
	//GMatrix L(size,0.0); 					// Initialize a Matrix
	srand(time(NULL));						// Set random seed
	for(int i=0;i<size;++i)
		for(int j=0;j<=i;++j)
			(*H)(i,j)=(rand() %101-50)/100.0; 	// Set lower tri

	for(int i=0;i<size;++i)
		for(int j=i+1;j<size;++j)
			(*H)(i,j)=(*H)(j,i); 			// Set upper tri

	for(int i=0;i<size;++i)
		(*H)(i,i)+=2.0;					// Dominate Diag
	//cout<<endl<<(*H)<<endl;

	// Generate random vector of linear coefficient c
	c = new GVector(size,0.0);
	for(int i=0;i<size;++i)
		(*c)[i]=(rand() %101 -50)/100.0;

	// Generate random vector of lower bound l
	l = new GVector(size);
	for(int i=0;i<size;++i)
		(*l)[i]=(rand() %101 -50)/100.0;

	// Generate random vector of upper bound u
	u = new GVector(size);
	for(int i=0;i<size;++i)
		(*u)[i]=(rand() %101)/100.0+(*l)[i];

};


// Printout Data of the problem
ostream& operator<<(ostream& out, BoundQpData& Bqp){
	std::cout<<"H:="<<endl
			 <<*Bqp.H<<endl;
	std::cout<<"c:="<<endl
			 <<*Bqp.c<<endl;
	std::cout<<"l:="<<endl
			 <<*Bqp.l<<endl;
	std::cout<<"u:="<<endl
			 <<*Bqp.u<<endl;
};

#endif /* BOUNDQPDATA_H_ */
