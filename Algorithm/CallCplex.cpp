/*
 * CallCplex.cpp
 *
 *  Created on: Feb 27, 2012
 *      Author: zheng
 */

// Call cplex directly to solve the problem

#include <iostream>
#include <ilcplex/ilocplex.h>
#include "CallCplex.h"


ILOSTLBEGIN

typedef IloArray<IloNumArray>    NumMatrix;
typedef IloArray<IloNumVarArray> NumVarMatrix;

void CallCplex(BoundQp* Bqp){

	IloEnv env;
	//env.setOut(env.getNullStream());


	int size = (*Bqp).getsize();
	IloInt Isz=(IloInt) size;
	IloModel model(env);

	// Extract data from H
	IloInt Ii;
	int i;
	//NumMatrix H(env, Isz);
	//for(Ii=0,i=0;i<size;i++,Ii++){
	//	//cout<<i<<endl;
	//	H[Ii] = IloNumArray(env,Isz);
	//	for(int j=0;j<size;j++){
	//		//cout<<j<<"\t";
	//		(H[Ii]).add((*(*Bqp).getH())(i,j));}
	//}

	// Extract data from c,l,u
	IloNumArray c(env);
	IloNumArray l(env);
	IloNumArray u(env);
	
	for(int i=0;i<size;++i){
		c.add((*(*Bqp).getg())[i]);
		l.add((*(*Bqp).getl())[i]);
		u.add((*(*Bqp).getu())[i]);
	}

	// Define Variables and formulate the bounds
	IloNumVarArray x(env);
	for(Ii=0;Ii<Isz;++Ii)
		x.add(IloNumVar(env,l[Ii],u[Ii]));

	// Formulate objective
	IloExpr obj(env);
	IloInt Ij;
	for(Ii=0;Ii<Isz;++Ii){
		for(Ij=0;Ij<Isz;++Ij)
			obj+=0.5*(*(*Bqp).getH())(int(Ii),int(Ij))*x[Ii]*x[Ij];}
	for(Ii=0;Ii<Isz;++Ii)
		obj+=c[Ii]*x[Ii];
	
	// Formulate the model
	model.add(IloMinimize(env,obj));
	obj.end();

	// Place that prints out license information

	IloCplex cplex(env);
	// Suppress displaying iterations
	cplex.setOut(env.getNullStream());


	// Call solver to solve the problem
	try{
		cplex.extract(model);
		cplex.solve();
	}
	catch (IloException& e) {
	      cerr << "ERROR: " << e.getMessage() << endl;
	   }


	// Print out optimal value and solution
	IloNumArray vals(env);
      	env.out() << "Solution status = " << cplex.getStatus() << endl;
      	env.out() << "Solution value  = " << cplex.getObjValue() << endl;
      	cplex.getValues(vals, x);
      	env.out() << "Values        = " << vals << endl;

      	// Access each value
      	//for(IloInt t=0;i<Isz;++i)
      	//	env.out()<<vals[i]<<endl;
	
	// Output .lp file
	//cplex.exportModel("BqpCplex.lp");

    // Update the solution in Bqp
    //Bqp->x = vals;

	// Close concert environment
	env.end();
};
