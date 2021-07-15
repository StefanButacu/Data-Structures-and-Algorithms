#include "Iterator.h"
#include "DO.h"
#include <stack>
using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
	p = dict.rad;
	stack < Nod* >  s;
	while (!s.empty() || p != nullptr) {
		while (p != nullptr) {
			s.push(p);
			p = p->st;
		}
		p = s.top();
		s.pop();
		elems.push_back(p->elem);
		p = p->dr;
	}
	curent = 0;
}

void Iterator::prim() {
	curent = 0;
}

void Iterator::urmator() {
	curent++;
}

bool Iterator::valid() const {

	return curent >= 0 && curent < elems.size();
}

TElem Iterator::element() const {
	
	return elems.at(curent);
}


