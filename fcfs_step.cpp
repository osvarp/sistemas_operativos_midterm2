/*
Autor: Oscar Vargas Pabon

First Come First Serve (FCFS)
*/
#include "fcfs_step.h"


int Fcfs_step::next_step_time() {
	assert( this->is_active() );
	return queue.front()->bt - queue.front()->completion;
}

std::pair<std::string,int> Fcfs_step::exec_step() {
	return this->exec_partial_step( this->next_step_time() );
}

std::pair<std::string,int> Fcfs_step::exec_partial_step( int tm ) {
	assert( this->next_step_time() >= tm );
	std::pair<std::string,int> res( queue.front()->name, tm );
	queue.front()->completion += tm;
	if ( queue.front()->completion == queue.front()->bt ) queue.pop_front();
	return res;
}

void Fcfs_step::add_process( Process *p ) { this->queue.push_back( p ); }

bool Fcfs_step::is_active() { return !this->queue.empty(); }