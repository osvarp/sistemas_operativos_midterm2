/*
Autor: Oscar Vargas Pabon

Shortest Time to Completion First (STCF)
*/
#include "stcf_step.h"

bool Stcf_comparator::operator ()( const Process *p1, const Process *p2 ){
	// p1 < p2
	bool res;
	int tc1 = p1->bt-p1->completion, tc2 = p2->bt-p2->completion;
	if ( tc1 != tc2 ) res = tc1 > tc2;
	else p1->name > p2->name;
	return res;
}


int Stcf_step::next_step_time() {
	assert( this->is_active() );
	return pq.top()->bt - pq.top()->completion;
}

std::pair<std::string,int> Stcf_step::exec_step() {
	return this->exec_partial_step( this->next_step_time() );
}

std::pair<std::string,int> Stcf_step::exec_partial_step( int tm ) {
	assert( this->next_step_time() >= tm );
	std::pair<std::string,int> res( pq.top()->name, tm );
	pq.top()->completion += tm;
	if ( pq.top()->completion == pq.top()->bt ) pq.pop();
	return res;
}

void Stcf_step::add_process( Process *p ) { this->pq.push( p ); }

bool Stcf_step::is_active() { return !this->pq.empty(); }
