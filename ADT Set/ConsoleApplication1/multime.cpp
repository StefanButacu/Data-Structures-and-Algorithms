#include "IteratorMultime.h"

#include "Multime.h"

#include <iostream>

void Multime::initBoolArray(){
	for (int i = 0; i < this->MaxElem - this->MinElem + 1; i++)
		this->elems[i] = false;
}

Multime::Multime() {
	/* de adaugat */
	this->MinElem = -5;
	this->MaxElem = 5;
	this->elems = (bool*) new bool[this->MaxElem - this->MinElem + 1];
	initBoolArray();
	this->N = 0;
}


bool Multime::adauga(TElem elem) {
	/* de adaugat */
	// Get The element from a position i in this bool array => elem = i + minElem
	// comlexitate  O(N) - pentru copiere , nu se mai poate amortiza  
	if (this->MinElem <= elem && elem <= this->MaxElem)
	{
		if (this->elems[elem - this->MinElem])  // inseamna ca era deja bagat
			return false;
		this->elems[elem - MinElem] = true;
	}
	else {
		if (elem < this->MinElem) {
			// trebuie sa mut toate elementele mai la dreapta cu (this->MinElem - elem)
			//                                de la dreapta la stanga pentru a nu pierde informatie
			// daca exista o pozitie care dupa shiftare trece de MaxElem trebuie alocat un nou spatiu
			bool* elemsCopy = (bool*) new bool[this->MaxElem - elem + 1];
			for (int i = this->MaxElem - this->MinElem; i >= 0; i--) {
				elemsCopy[i + this->MinElem - elem] = this->elems[i];
			}
			for (int i = 0; i < this->MinElem - elem; i++)
				elemsCopy[i] = false;
			elemsCopy[0] = true; 
			this->MinElem = elem;
			free(this->elems);
			this->elems = elemsCopy;
		}
		else {
			// aici in dreapta nu tre
			bool* elemsCopy = (bool*) new bool[elem - this->MinElem + 1];
			for (int i = 0; i <= this->MaxElem - this->MinElem; i++)
				elemsCopy[i] = this->elems[i];   // copiez ce era anterior salvat
			for (int i = this->MaxElem - this->MinElem + 1 ; i <= elem-this->MinElem; i++) {
				elemsCopy[i] = false ;
			}
			elemsCopy[elem - this->MinElem] = true;
			this->MaxElem = elem;
			free(this->elems);
			this->elems = elemsCopy;

		}
	}
	this->N++;
	return true;
}


bool Multime::sterge(TElem elem) {
	/* Complexitate timp theta(1) */
	// daca e in afara intervalului 
	if (elem < this->MinElem || elem > this->MaxElem)
		return false;
	// daca era in multime 
	if (this->elems[elem - this->MinElem]) {
		this->elems[elem - this->MinElem] = false;
		this->N--;
		return true;
	}
	// daca nu era in multime
	return false;
}


bool Multime::cauta(TElem elem) const {
	/* de Complexitate timp theta(1) */
	// este in afara intervalului
	if (elem < this->MinElem || elem > this->MaxElem)
		return false;

	// este in intervalul meu de reprezentare 
	return this->elems[elem-this->MinElem];
}


int Multime::dim() const {
	// Complexitate timp theta(1)
	return this->N;
}

bool Multime::vida() const {
	/* Complexitate timp theta(1) */ 
	if(this->dim() == 0)
		return true;
	return false;
}


Multime::~Multime() {
	/* de adaugat */
	delete[] this->elems;
}



IteratorMultime Multime::iterator() const {
	return IteratorMultime(*this);
}

