#include <iostream>
#include "../DataStructure/BoundQpData.h"
#include "../DataStructure/GVector.h"

// An example that uses DataStructure for BoundQp
using namespace std;
int main(){
  // Initialize data
  GMatrix A(2);					// Initialize a GMatrix
  A(0,0)=1.0;A(0,1)=1.0;A(1,0)=1.0;A(1,1)=1.0;  // Assign data to GMatrix
  GVector B(2,1.0);				// Initialize a GVector
  GVector c=A*B;				// GVector*GMatrix, return a GVector c
  GVector e=B*A;				// GMatrix*GVector, return a GVector e
  
  // Print out data
  cout<<"GMatrix A:"<<endl;
  cout<<A<<endl;
  cout<<"GVector c and e:"<<endl;
  cout<<c<<endl
      <<e<<endl;
	
  // Print out multiplication results				
  double f=e*e;					// GVector*GVector, return a scalar
  double d=c*c;					
  cout<<"f=e*e:"<<endl
	<<d<<endl<<endl;
  cout<<"d=c*c:"<<endl
	<<f<<endl<<endl;  

  // BoundQpData
  BoundQpData tmp(4);				// Initialize a BoundQpData
  tmp.MakeRandomData();				// Generate random data
  cout<<"BoundQpData contains:"<<endl
	<<tmp;							// Print generated data

  //cout<<tmp.H(1,1);
  return 0;
}
