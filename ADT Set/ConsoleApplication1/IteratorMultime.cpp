#include "IteratorMultime.h"
#include "Multime.h"
#include <exception>
#include <iostream>
using namespace std;

IteratorMultime::IteratorMultime(const Multime& m) : multime(m) {
	/* O(MaxElem) - de obicei pe pozitia 0 se afla cel mai mic element care apartine multimii
	se fac mai multi pasi in caz ca se adauga tot timpul elemente > MaxElem*/
	this->pozCurenta = 0;
	while (multime.elems[this->pozCurenta] == false)
		this->pozCurenta++;
}


void IteratorMultime::prim() {
	/*  O(MaxElem) - de obicei pe poziita 0 se afla cel mai mic element
	se fac mai multi pasi in caz ca se adauga tot timpul elemente > MaxElem
	*/
	this->pozCurenta = 0;
	while (this->pozCurenta < multime.MaxElem - multime.MinElem + 1 && multime.elems[this->pozCurenta] == false)
		this->pozCurenta++;

}


void IteratorMultime::urmator() {
	/* Theta(1) */
	this->pozCurenta++;

	while (this->pozCurenta < multime.MaxElem - multime.MinElem + 1) {
		if (multime.elems[this->pozCurenta])
			break;
		this->pozCurenta++;
	}
}


TElem IteratorMultime::element() const {
	/* Theta(1) */
	// elem = i + minElem
	if (!valid())
		throw exception();
	return this->pozCurenta + multime.MinElem;
}

bool IteratorMultime::valid() const {
	/* Theta(1) */
	return this->pozCurenta < multime.MaxElem - multime.MinElem + 1 && multime.elems[this->pozCurenta];
	/*if (multime.elems[this->pozCurenta] == true)
		return true;
	return false;
	*/
}
