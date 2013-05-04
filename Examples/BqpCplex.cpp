/*
 * BqpManip.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: zheng
 */

#include "../Gpdas/BoundQp.h"
#include "../Gpdas/BoundQp.cpp"
#include <string>
int main(){
	// Create a BoundQp class instance with 10 vars
	BoundQp bqp(10);
	bqp.MakeRandomData();
	// print out parameters (H,c,l,u)
	cout<<bqp;
	// print out initial solution (x,zl,zu)
	cout<<*bqp.x<<endl;
	cout<<*bqp.zl<<endl;
	cout<<*bqp.zu<<endl;
	//cout<<(*bqp.getH())(1,1);
	// Create a BoundQpData class instance with 10 vars
	BoundQpData bd(10);
	bd.MakeRandomData();
	//cout<<*bd.getg()<<endl;
	bqp.optimize();
	// Print out the optimized solution (x,zl,zu)
	cout<<*bqp.x<<endl;
	cout<<*bqp.zl<<endl;
	cout<<*bqp.zu<<endl;
	//cout<<*bqp.x;
	return 0;
}
