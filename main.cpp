/*
Autor: Oscar Vargas Pabon
Fecha: 31/03/2025

Haciendo varios schedulers.
*/

#include "primitives.h"
#include "scheduler_algo.h"
#include "mlq.h"
#include "rr_step.h"
#include "fcfs_step.h"
#include "stcf_step.h"
#include "sjf_step.h"

#include <stdio.h>
#include <iostream>

#include <string>
#include <list>
#include <vector>
#include <map>

///////////////////////////// processing

// sched_algo : [event,...] -> [ ( name, time ),...]
std::map<std::string,std::vector<int>> statistics( const std::list<Event*> &proc, const std::list<std::pair<std::string,int>> &diag ) {
	std::map<std::string,std::vector<int>> stat;
	int time = 0;
	for ( const std::pair<std::string,int> &ev : diag ) {
		if ( ev.first == no_proc ) {
			time += ev.second;
			continue;
		}
		
		if ( !stat.count(ev.first) ) {
			stat[ev.first] = std::vector<int>( 4, 0 );
			stat[ev.first][rt] = time;
		}
		
		stat[ev.first][wt] -= ev.second;
		
		time += ev.second;
		stat[ev.first][ct] = time;
	}
	for ( const Event *e : proc ) {
		stat[e->p->name][tat] = stat[e->p->name][ct] - e->at;
		stat[e->p->name][wt] += stat[e->p->name][tat];
	}
	return stat;
}
// statistics : [event,...]X[(nm,tm),...] -> [ct, rt, wt, tat]
std::vector<double> find_averages( const std::map<std::string,std::vector<int>> &stat ){
	std::vector<double> aggl( 4, 0.0 );
	for ( const std::pair<std::string,std::vector<int>> &st : stat ) {
		aggl[ct] += st.second[ct];
		aggl[rt] += st.second[rt];
		aggl[wt] += st.second[wt];
		aggl[tat]+=st.second[tat];
	}
	for ( int i = 0 ; i < int(aggl.size()) ; ++i ) {
		aggl[i] /= stat.size();
	}
	return aggl;
}

//////////////////// reading
void flush_line(){
	char t;
	do {
		t = getc( stdin );
	} while ( t != '\n' && t != EOF );
}

std::string my_read_str(){
	char t;
	do {
		t = getc( stdin );
	} while ( !('a'<=t && t<='z') && t!='-' && t != '#' && !('A'<=t && t <= 'Z') && !('0'<=t && t <= '9') && t != EOF );
	
	if ( t == '#' ) {
		flush_line();
		return my_read_str();
	}
	
	std::string str;
	while ( t != ';' && t != '	' && t != ' ' && t != '\n' && t != EOF ) {
		str.push_back( t );
		t = getc( stdin );
	}
	return str;
}
int str_to_int( const std::string &str ){
	int res = 0; bool sgn = str[0] == '-';
	for ( int i = (sgn)?1:0 ; i < int(str.size()) ; ++i ) {
		res = res*10 + str[i]-'0';
	}
	if ( sgn ) res = -res;
	return res;
}
int my_read_int(){
	return str_to_int( my_read_str() );
}

std::list<Event*> process_reader(){
	// Para leer de stdin los procesos
	std::list<Event*> proc;
	std::string act = my_read_str();
	while ( !feof( stdin ) ) {
		int bt, at, q, pr;
		bt = my_read_int(); at = my_read_int(); q = my_read_int(); pr = my_read_int();
		proc.push_back( new Event(at, q, new Process(act, bt, pr) ) );
		act = my_read_str();
	}
	return proc;
}
///////////////////////////// writing

void output( const std::list<Event*> &proc, const std::list<std::pair<std::string,int>> &diag ) {
	std::map<std::string,std::vector<int>> stat = statistics( proc, diag );
	std::vector<double> agg = find_averages( stat );
	std::cout << "# Powered by Oscar\n";
	std::cout << "# etiqueta; BT; AT; Q; Pr; WT; CT; RT; TAT\n";
	for ( const Event *e : proc ) {
		std::vector<int> &ss = stat[e->p->name];
		std::cout << e->p->name << " ; " << e->p->bt << " ; " << e->at << " ; " << e->q << " ; " << e->p->pr << " ; ";
		std::cout << ss[wt] << " ; " << ss[ct] << " ; " << ss[rt] << " ; " << ss[tat] << ";\n";
	}
	std::cout << "WT=" << agg[wt] << "; CT=" << agg[ct] << "; RT=" << agg[rt] << "; TAT=" << agg[tat] << ";\n";
}

/////////////  ggs

int main( int argc, char *argv[]){
	// set the sched algo
	std::vector<SchedStep*> algo;
	int quanta = -1, standard=5;
	if ( argc == 1 || argv[1][0] != '-' ) quanta = standard;
	else if ( argv[1][1] == '1' ) {
		std::cerr << "Info: Ejecutando un MLQ< RR(1), RR(3), SJF >.\n";
		algo = std::vector<SchedStep*>(
			{ new Rr_step( 1 ), new Rr_step( 3 ), new Sjf_step() });
	}else if ( argv[1][1] == '2' ) {
		std::cerr << "Info: Ejecutando un MLQ< RR(3), RR(5), FCFS >.\n";
		algo = std::vector<SchedStep*>(
			{ new Rr_step( 3 ), new Rr_step( 5 ), new Fcfs_step() });
	}else if ( argv[1][1] == '3' ) {
		std::cerr << "Info: Ejecutando un MLQ< RR(2), RR(3), STCF >.\n";
		algo = std::vector<SchedStep*>(
			{ new Rr_step( 2 ), new Rr_step( 3 ), new Stcf_step() });
	} else if ( argv[1][1] == '4' ) {
		std::cerr << "Info: Ejecutando un First Come First Serve (FCFS).\n";
		algo = std::vector<SchedStep*>( { new Fcfs_step() } );
	} else if ( argv[1][1] == '5' ) {
		std::cerr << "Info: Ejecutando un Shortest Time to Completion First (STCF).\n";
		algo = std::vector<SchedStep*>( { new Stcf_step() } );
	} else if ( argv[1][1] == '6' ) {
		std::cerr << "Info: Ejecutando un Shortest Job First (SJF).\n";
		algo = std::vector<SchedStep*>( { new Sjf_step() } );
	} else quanta = standard;
	
	if ( quanta != -1 ) {
		std::cerr << "Info: Ejecutando un RoundRobin con quanta "<< quanta << '\n';
		algo = { new Rr_step( quanta ) };
	}
	SchedAlgo *to_use = new Mlq( algo );
	
	std::list<Event*> proc = process_reader();
	
	// for ( Event *e : proc ) {
		// std::cout << e->p->name << " | " << e->p->bt << " | "<< e->at << " | " << e->q << " | " << e->p->pr << std::endl;
	// }
	
	for ( Event *e : proc ) assert ( e->q < int(algo.size()) );
	
	std::list<std::pair<std::string,int>> diag = to_use->exec( proc );
	
	output( proc, diag );
	
	return 0;
}