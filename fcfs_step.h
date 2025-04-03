/*
Autor: Oscar Vargas Pabon

First Come First Serve (FCFS)
*/
#ifndef FCFS_STEP_H
#define FCFS_STEP_H

#include "scheduler_algo.h"
#include "primitives.h"
#include <string>
#include <list>
#include <cassert>


class Fcfs_step : public SchedStep{
	private:
	std::list<Process*> queue;
	public:
	Fcfs_step() : SchedStep( false ) {};
	int next_step_time() override ;
	std::pair<std::string,int> exec_step() override;
	std::pair<std::string,int> exec_partial_step( int ) override;
	void add_process( Process * ) override;
	bool is_active() override;
};

#endif // FCFS_STEP_H