/*
Autor: Oscar Vargas Pabon

Shortest Time to Completion First (STCF)
*/
#ifndef STCF_STEP_H
#define STCF_STEP_H

#include "scheduler_algo.h"
#include "primitives.h"
#include <string>
#include <queue>
#include <vector>
#include <cassert>


class Stcf_comparator {
	public:
	bool operator ()( const Process *, const Process * );
};

class Stcf_step : public SchedStep{
	private:
	std::priority_queue<Process*,std::vector<Process*>,Stcf_comparator> pq;
	public:
	Stcf_step() : SchedStep( true ) {};
	int next_step_time() override ;
	std::pair<std::string,int> exec_step() override;
	std::pair<std::string,int> exec_partial_step( int ) override;
	void add_process( Process * ) override;
	bool is_active() override;
};

#endif // STCF_STEP_H