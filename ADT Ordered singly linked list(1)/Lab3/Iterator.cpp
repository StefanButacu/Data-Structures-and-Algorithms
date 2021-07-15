#include "Iterator.h"
#include "LO.h"
#include <exception>

Iterator::Iterator(const LO& lo) : lo(lo) {
	/* Theta(1) */
	this->prim();
}

void Iterator::prim() {
	/* Theta(1) */
	p = lo.primul;
}

void Iterator::urmator() {
	/* Theta(1) */
	if (!this->valid())
		throw std::exception();
	p = p->next;
}

bool Iterator::valid() const {
	/* Theta(1) */
	return p != nullptr;
}

TElement Iterator::element() const {
	/* Theta(1) */
	if (this->valid())
		return p->val;
	else
		throw std::exception();
}


void Iterator::avanseazaKPasi(int k)
{
	/* avanseazaKPasi(k, p) 
	Pre - k intreg 
	    - p iterator 
	Post: - cursorul este mutat cu k elemente 

	subalgortim avanseazaKPasi(k, p)
		daca k <= 0 atunci 
			arunca exceptie
		sf daca
		daca valid(p) == fals atunci
			arunca exceptie
		sf daca 
		i = 0
		cat timp ( i < k si valid(p) ) executa 
			i += 1 
			urmator(p);
		sf cat timp
		daca p = NIL atunci
			arunca exceptie
		sf daca
	sf subalgoritm
	*/
	/// Complexitate generala timp - O(min(N,K)) -(caz fav = caz nefav = caz mediu)  tot timpul se efectueaza exact k pasi  
	if (k <= 0)
		throw std::exception();
	if (!this->valid())
		throw std::exception();	
	int i = 0;
	while( i < k && this->valid()) {
		this->urmator();
		i++;
	}
	if (!this->valid()) // forul s a terminat din cauza ca  
		p = nullptr ;   // sunt mai putin de k elemente ramase in lista 
	// daca am ajuns aici inseamna ca am facut k pasi 	
	
}


