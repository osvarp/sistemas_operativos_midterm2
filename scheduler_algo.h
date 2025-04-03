#ifndef SCHEDULER_ALGO_H
#define SCHEDULER_ALGO_H

#include "primitives.h"
#include<list>
class SchedAlgo{
	public:
	SchedAlgo() = default;
	virtual std::list<std::pair<std::string,int>> exec ( std::list<Event*> & )=0;
};

class SchedStep{
	private:
	bool m_preemptive;
	public:
	SchedStep( bool p=0 ) : m_preemptive(p) {};
	virtual int next_step_time() = 0;
	virtual std::pair<std::string,int> exec_step() = 0;
	virtual std::pair<std::string,int> exec_partial_step( int ) = 0;
	virtual void add_process( Process * ) = 0;
	virtual bool is_active() = 0;
	bool is_m_preemptive() { return this->m_preemptive; }
};

#endif // SCHEDULER_ALGO_H