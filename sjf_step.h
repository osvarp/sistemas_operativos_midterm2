/*
Autor: Oscar Vargas Pabon

Shortest Job First (SJF)
*/
#ifndef Sjf_step_H
#define Sjf_step_H

#include "scheduler_algo.h"
#include "primitives.h"
#include <string>
#include <queue>
#include <vector>
#include <cassert>


class Sjf_comparator {
	public:
	bool operator ()( const Process *, const Process * );
};

class Sjf_step : public SchedStep{
	private:
	std::priority_queue<Process*,std::vector<Process*>,Sjf_comparator> pq;
	public:
	Sjf_step() : SchedStep( false ) {};
	int next_step_time() override ;
	std::pair<std::string,int> exec_step() override;
	std::pair<std::string,int> exec_partial_step( int ) override;
	void add_process( Process * ) override;
	bool is_active() override;
};

#endif // Sjf_step_H