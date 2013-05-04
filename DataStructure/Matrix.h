/*
 * Matrix.h
 *
 *  Created on: Feb 21, 2012
 *      Author: zheng
 */

#ifndef MATRIX_H_
#define MATRIX_H_

#include <iostream>
#include <iomanip>

// A general matrix class, modified from
// http://www.parashift.com/c++-faq-lite/operator-overloading.html#faq-13.10
using namespace std;

class Matrix {

public:
   Matrix();
   Matrix(int rows, int cols);
   Matrix(int rows, int cols, double val);
   double& operator() (int row, int col);
   double  operator() (int row, int col) const;

  ~Matrix();                              // Destructor
   Matrix(Matrix const& m);               // Copy constructor
   Matrix& operator= (Matrix const& m);   // Assignment operator
   // Overloading printout
   friend ostream& operator<< (ostream& out, Matrix &Mat);

 protected:
   int rows_, cols_;
   double* data_;
 };

 inline
 Matrix::Matrix(int rows, int cols)
   : rows_ (rows)
   , cols_ (cols)
   //data_ <--initialized below (after the 'if/throw' statement)
 {
   if (rows == 0 || cols == 0)
     std::cerr<<"Matrix constructor has 0 size";
   data_ = new double[rows * cols];
 }

 inline
 Matrix::Matrix(int rows, int cols, double val)
   : rows_ (rows)
   , cols_ (cols)
   //data_ <--initialized below (after the 'if/throw' statement)
 {
   if (rows == 0 || cols == 0)
     std::cerr<<"Matrix constructor has 0 size";
   data_ = new double[rows * cols];
   for(int i=0;i<rows*cols;++i)
	   data_[i]=0.0;
 }

 inline
 Matrix::~Matrix()
 {
   delete[] data_;
 }

 inline
 double& Matrix::operator() (int row, int col)
 {
   if (row >= rows_ || col >= cols_)
     //throw BadIndex("Matrix sub"
	   cerr << "Matrix sub"
    		 "script out of bounds"<<endl;
   return data_[cols_*row + col];
 }

 inline
 double Matrix::operator() (int row, int col) const
 {
   if (row >= rows_ || col >= cols_)
     //throw BadIndex("const Matrix subscript out of bounds");
   return data_[cols_*row + col];
 }

 ostream& operator<<(ostream& out,Matrix& mat){
	 for(int i=0;i<mat.rows_;++i){
		 for(int j=0;j<mat.cols_;++j)
			 out<<std::setw(6)<<right<<mat(i,j)<<" ";
		 out<<endl;}
	 // End with flushing buffer otherwise segmentation fault
	 out<<endl;

 };

#endif /* MATRIX_H_ */
