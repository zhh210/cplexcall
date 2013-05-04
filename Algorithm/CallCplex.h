/*
 * CallCplex.h
 *
 *  Created on: Feb 27, 2012
 *      Author: zheng
 */


// Call Cplex to solve the problem

//#include "../../../../../../usr/local/CPLEX_Studio_123/cplex/include/ilcplex/ilocplex.h"
#include <ilcplex/ilocplex.h>
#include "../Gpdas/BoundQp.h"
#ifndef CALLCPLEX_H_
#define CALLCPLEX_H_
void CallCplex(BoundQp* bqp);

#endif /* CALLCPLEX_H_ */
