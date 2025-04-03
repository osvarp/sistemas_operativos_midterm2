#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <string>

#define ct 0
#define rt 1
#define wt 2
#define tat 3

const std::string no_proc = "NULL";

class Process{
	public:
	std::string name;
	int bt,pr, completion;
	Process()=default;
	Process( const Process &p ) : name(p.name), bt(p.bt), pr(p.pr), completion(0) {};
	Process( const std::string &nm, int btt, int prr ) : name(nm), bt(btt),pr(prr), completion(0){};
};

class Event{
	public:
	Process *p;
	int at, q;
	
	Event()=default;
	Event( int att, int qq, Process *pp ) : at(att),q(qq), p(pp){};
	~Event() { delete this->p; }
};
#endif //PRIMITIVES_H