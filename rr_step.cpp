/*
Autor: Oscar Vargas Pabon
Un Round Robin (RR)
*/
#include "rr_step.h"


Rr_step::Rr_step( int q=0 ) : SchedStep( false ) {
	this->quanta = q;
	this->it = round.begin();
}

int Rr_step::next_step_time(){
	assert( this->is_active() );
	if ( it == this->round.end() ) it = this->round.begin();
	return std::min(this->quanta, (*it)->bt - (*it)->completion );
}
std::pair<std::string,int> Rr_step::exec_step() {
	return exec_partial_step( this->next_step_time() );
}
std::pair<std::string,int> Rr_step::exec_partial_step( int time ) {
	assert( time <= this->next_step_time() );
	// casos raros pueden pasar
	if ( it == this->round.end() ) it = this->round.begin();
	
	std::pair<std::string,int> res( (*it)->name, time );
	(*it)->completion += time;
	
	// actualizar el iterador
	if ( (*it)->bt == (*it)->completion ) {
		// ya termino
		it = this->round.erase( it );
	} else ++it;
	if ( it == this->round.end() ) it = this->round.begin();
	
	return res;
}
void Rr_step::add_process( Process *nw ) {
	// anadir al indice anterior a it?????
	this->round.push_back( nw );
}

bool Rr_step::is_active() { return !this->round.empty(); }