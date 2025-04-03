/*
Autor: Oscar Vargas Pabon
Un Multi Level Queue (MLQ)
*/
#ifndef MLQ_H
#define MLQ_H

#include "primitives.h"
#include "scheduler_algo.h"
#include <list>
#include <string>
#include <queue>
#include <cassert>

class Mlq_comparator {
	public:
	bool operator () ( const Event *, const Event * );
};

class Mlq : public SchedAlgo {
	std::vector<SchedStep*> algo;
	int find_first_active( int );
	
	public:
	Mlq( std::vector<SchedStep*> alg ) : algo(alg) {};
	std::list<std::pair<std::string,int>> exec( std::list<Event*> & ) override;
};

#endif // MLQ_H
