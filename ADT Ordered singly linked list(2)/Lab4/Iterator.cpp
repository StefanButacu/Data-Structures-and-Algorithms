#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO& lo) : lo(lo) {
	/* de adaugat */
	curent = lo.head;
}//Theta(1)

void Iterator::prim() {
	/* de adaugat */
	curent = lo.head;
}//Theta(1)

void Iterator::urmator() {
	/* de adaugat */
	if (curent == -1)
		throw std::exception();
	curent = lo.urm[curent];
}//Theta(1)

bool Iterator::valid() const {
	/* de adaugat */
	return curent != -1 ;
}//Theta(1)

TElement Iterator::element() const {
	/* de adaugat */
	if (curent == -1)
		throw std::exception();
	return lo.elems[curent];
}//Theta(1)


