/*
Autor: Oscar Vargas Pabon

Shortest Job First (SJF)
*/
#include "sjf_step.h"

bool Sjf_comparator::operator ()( const Process *p1, const Process *p2 ){
	// p1 < p2
	bool res;
	if ( p1->bt != p2->bt ) res = p1->bt > p2->bt;
	else p1->name > p2->name;
	return res;
}


int Sjf_step::next_step_time() {
	assert( this->is_active() );
	return pq.top()->bt - pq.top()->completion;
}

std::pair<std::string,int> Sjf_step::exec_step() {
	return this->exec_partial_step( this->next_step_time() );
}

std::pair<std::string,int> Sjf_step::exec_partial_step( int tm ) {
	assert( this->next_step_time() >= tm );
	std::pair<std::string,int> res( pq.top()->name, tm );
	pq.top()->completion += tm;
	if ( pq.top()->completion == pq.top()->bt ) pq.pop();
	return res;
}

void Sjf_step::add_process( Process *p ) { this->pq.push( p ); }

bool Sjf_step::is_active() { return !this->pq.empty(); }