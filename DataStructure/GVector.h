/*
 * GVector.h
 *
 *  Created on: Feb 21, 2012
 *      Author: zheng
 */

#ifndef GVECTOR_H_
#define GVECTOR_H_

#include <iostream>


// Vector class
class GVector{
public:
	//GVector();
	GVector(int n);
	GVector(int n,double value);
	double& operator[] (int n);
	double operator[] (int n) const;

	~GVector();					// Destructor
	GVector(GVector const& v);	// Copy constructor
	GVector& operator=(GVector const& v); // Assignment constructor
	friend ostream& operator<< (ostream& out,const GVector& vec);
	friend double operator * (GVector& vec);
	friend GVector& operator + (GVector& vec);
	int getsize(){return size;}
protected:
	int size;
	double* data;
};

inline
GVector::GVector(int n):size(n){
	data = new double[n];
};

inline
GVector::GVector(int n,double value):size(n){
	data = new double[n];
	for(int i=0;i<n;i++)
		data[i]=value;
};

inline
GVector::~GVector(){
	delete[] data;
};

inline
double& GVector::operator[] (int n){
	if(n<0||n>=size)
		cerr<< "Vector subscript out of range."<<endl;
	return data[n];
};

inline
double GVector::operator[] (int n) const{
	if(n<0||n>=size)
		cerr<< "Vector subscript out of range."<<endl;
	return data[n];
};


double operator* (GVector& v1,GVector& v2){
	if(v1.getsize() != v2.getsize())
		cerr<<"Inner product of vectors should "
				"have same dimension."<<endl;
	double result = 0.0;
	for(int i=0;i<v1.getsize();i++)
		result+=v1[i]*v2[i];
	return result;
};

GVector operator + (GVector& v1, GVector& v2){
	if(v1.getsize() != v2.getsize())
		cerr<<"Sum of vectors should "
				"have same dimension."<<endl;
	int size = v1.getsize();
	GVector result = GVector(size);
	for(int i=0;i<size;++i)
		result[i] = v1[i]+v2[i];
	return result;
};

ostream& operator<< (ostream& out,GVector& vec){
	for(int i=0;i<vec.getsize();++i)
		cout<<setw(6)<<right<<vec[i]<<" ";
	cout<<endl;
	return out;
};

#endif /* GVECTOR_H_ */
