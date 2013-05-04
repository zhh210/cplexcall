/*
 * GMatrix.h
 *
 *  Created on: Feb 21, 2012
 *      Author: zheng
 */

#ifndef GMATRIX_H_
#define GMATRIX_H_

#include <iostream>
#include "Matrix.h"
#include "GVector.h"

class GMatrix;
class GVars;
class Matrix;
class GVector;

using namespace std;

// Matrix class
class GMatrix:public Matrix {
public:
	int size; // Size of the squared matrix

	GMatrix(int n):Matrix(n,n),size(n){};
	GMatrix(int n, double v):Matrix(n,n,v),size(n){};
	~GMatrix(){};
	friend GVector operator * (GVector& vec, GMatrix& mat);
	friend GVector operator * (GMatrix& mat, GVector& vec);
	friend GMatrix operator * (GMatrix& m1, GMatrix& m2);
};


GVector operator *(GVector& vec, GMatrix& mat){
	GVector result (mat.size,0.0);
	for(int i=0;i<mat.size;i++)
		for(int j=0;j<mat.size;j++)
			result[i]+=vec[j]*mat(j,i);
	return result;
};

GVector operator * (GMatrix& mat, GVector& vec){
	GVector result(mat.size,0.0);
	for(int i=0;i<mat.size;i++)
		for(int j=0;j<mat.size;j++)
			result[i]+=mat(i,j)*vec[j];
	return result;
};

GMatrix operator *(GMatrix& m1,GMatrix& m2){
	if(m1.size != m2.size)
		cerr<<"Inconsistent matrices multiplication"<<endl;
	GMatrix result(m1.size,0.0);
	for(int i=0;i<m1.size;++i)
		for(int j=0;j<m1.size;++j)
			for(int k=0;k<m1.size;++k)
			result(i,j)+=m1(i,k)*m2(k,j);

	return result;
};

#endif /* GMATRIX_H_ */
