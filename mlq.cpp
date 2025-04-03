/*
Autor: Oscar Vargas Pabon
Un Multi Level Queue (MLQ)
*/
#include "mlq.h"
#include <iostream>

bool Mlq_comparator::operator ()( const Event *e1, const Event *e2 ) {
	// e1 < e2
	bool res;
	if ( e1->at != e2->at ) res = e1->at > e2->at;
	else res = e1->p->name > e2->p->name; 
	return res;
}


int Mlq::find_first_active( int strt=0 ){
	int res = -1;
	for ( int i = std::max(strt,0) ; i < int(algo.size()) && res == -1 ; ++i ) {
		if ( this->algo[i]->is_active() ) res = i;
	}
	return res;
}

std::list<std::pair<std::string,int>> Mlq::exec( std::list<Event*> &proc ) {
	std::list<std::pair<std::string,int>> diag;
	
	std::priority_queue<Event*,std::vector<Event*>,Mlq_comparator> pq;
	for ( Event *e : proc ) pq.push( e );
	
	int fa=-1,tm=0, prev_q=-1; // fa -> first active, tm -> time
	std::list<std::pair<int,Process*>> np_q; // non_preemptive queue
	auto execute_all_posible = [&] ( int tope ) {
		// ejecuto todo lo posible
		fa = this->find_first_active( fa );
		while ( fa != -1 && algo[fa]->next_step_time()+tm < tope ) {
			tm += algo[fa]->next_step_time();
			diag.push_back( algo[fa]->exec_step() );
			
			while ( !np_q.empty() && np_q.front().first < tm ) {
				algo[fa]->add_process( np_q.front().second );
				np_q.pop_front();
			}
			
			fa = this->find_first_active( fa );
		}
	};
	while ( !pq.empty() ) {
		Event *act = pq.top(); pq.pop();
		execute_all_posible( act->at );
		if ( fa!=-1 && 
			( act->q < fa || ( act->q==fa && algo[fa]->is_m_preemptive() ) ) ) {
			diag.push_back( algo[fa]->exec_partial_step( act->at-tm ) );
			tm = act->at;
			fa = act->q;
		}
		if ( fa != prev_q ) {
			while ( !np_q.empty() ) {
				algo[fa]->add_process( np_q.front().second );
				np_q.pop_front();
			}
			prev_q = fa;
		}
		if ( fa == -1 || algo[fa]->is_m_preemptive() || act->q > fa || tm == act->at ) {
			algo[act->q]->add_process( act->p );
		} else {
			np_q.push_back( std::pair<int,Process*>( act->at, act->p ) );
		}
	}
	execute_all_posible( 1e9 );
	return diag;
}