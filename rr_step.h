/*
Autor: Oscar Vargas Pabon
Un Round Robin (RR)
*/
#ifndef RR_STEP_H
#define RR_STEP_H

#include "scheduler_algo.h"
#include "primitives.h"
#include <string>
#include <cassert>

class Rr_step : public SchedStep{
	private:
	int quanta;
	std::list<Process*> round;
	std::list<Process*>::iterator it;
	public:
	Rr_step( int );
	int next_step_time() override ;
	std::pair<std::string,int> exec_step() override;
	std::pair<std::string,int> exec_partial_step( int ) override;
	void add_process( Process * ) override;
	bool is_active() override;
};

#endif // RR_STEP_H