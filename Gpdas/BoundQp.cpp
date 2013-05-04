/*
 * BoundQp.cpp
 *
 *  Created on: Feb 21, 2012
 *      Author: zheng
 */

#include <iostream>
#include <vector>
#include "BoundQp.h"
#include "../Algorithm/CallCplex.h"
#include "../Algorithm/CallCplex.cpp"

// For Pdas: update partition
void BoundQp::update_partition(){

};
// For Pdas: update variables
void BoundQp::update_vars(){
	// Update zl,zu for index set I
	if(!this->I.empty())
		for(vector<int>::iterator i=this->I.begin();i<this->I.end();++i){
			int index = *i;
			(*this->zl)[index]=0;
			(*this->zu)[index]=0;
		}
	// Update x,zu for index set L
	if(!this->L.empty())
		for(vector<int>::iterator i=this->L.begin();i<this->L.end();++i){
			int index = *i;
			(*this->x)[index]=(*this->l)[index];
			(*this->zu)[index]=0;
		}
	// Update x,zl for index set U
	if(!this->U.empty())
		for(vector<int>::iterator i=this->U.begin();i<this->U.end();++i){
			int index = *i;
			(*this->x)[index]=(*this->u)[index];
			(*this->zu)[index]=0;
		}

	// Update x[I] (using cplex)
	ILOSTLBEGIN
	IloEnv env;


	int size = this->I.size();
	IloInt Isz = (IloInt) size;
	IloModel model(env);

	IloInt Ii;
	int i;
	IloNumArray c(env);
	//IloNumArray l(env);
	//IloNumArray u(env);

	IloNumVarArray x(env);
	for(vector<int>::iterator it=this->I.begin();it<this->I.end();++i){
		int index = *it;
		c.add((*this->getg())[index]);
		x.add(IloNumVar(env));
	}

	// Formulate objective
	IloExpr obj(env);
	IloInt Ij;
	for(Ii=0;Ii<Isz;++Ii){
		for(Ij=0;Ij<Isz;++Ij)
			obj+=0.5*(*this->getH())(int(Ii),int(Ij))*x[Ii]*x[Ij];}
	for(Ii=0;Ii<Isz;++Ii)
		obj+=c[Ii]*x[Ii];

	model.add(IloMinimize(env,obj));
	obj.end();
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

	IloNumArray vals(env);
	cplex.getValues(vals, x);
	// Replace x[I] by the solution of cplex
	vector<int>::iterator it=this->I.begin();
	for(IloInt Ii=0;Ii<Isz;++Ii,++it){
		int index = *it;
		(*this->x)[index] = vals[Ii];
	}

	// Update zl[L] and zu[U]
	GVector z = (*this->getH())*(*this->x);
	if(!this->L.empty())
		for(vector<int>::iterator it=this->L.begin();it<this->L.end();++it){
			int index = *it;
			(*this->zl)[index] = z[index];
		}

	if(!this->U.empty())
		for(vector<int>::iterator it=this->U.begin();it<this->U.end();++it){
			int index = *it;
			(*this->zu)[index] = z[index];
		}
};

// Check optimality
bool BoundQp::is_optimal(){
	//std::cout<<this->x;
	for(int i=0;i<(this->getsize());++i){
			if((*this->x)[i]<(*this->l)[i]
			        || (*this->x)[i]>(*this->u)[i]
			        || (*this->zl)[i]<0.0
			        || (*this->zu)[i]<0.0)
				return false;}
	return true;
};

// Print out current iteration
void BoundQp::print(){

};

void BoundQp::optimize(){
	// Solve directly with cplex
	std::cout<<"Start optimizing with cplex:"<<endl;
	CallCplex(this);

	// Solve with PDAS
	std::cout<<"Start optimizing with PDAS:"<<endl;

	// Initialize partition (L,U,I) by default I=1:n
	this->I.clear();
	for(int i=0;i<this->getsize();++i)
		// All indices are inactive
		this->I.push_back(i);
	this->L.clear();
	this->U.clear();

	// Initialize (x,zl,zu) according to the partition
	this->update_vars();

	while(!this->is_optimal()){
		//cout<<"Not optimal"<<endl;
		// Update partition according to current variables' value
		this->update_partition();
		// Update variables' value according to current partition
		this->update_vars();
		// Print out current iteration
		this->print();
	};

}




