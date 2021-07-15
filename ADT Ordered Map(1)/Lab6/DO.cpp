#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

void DO::redim() {
	TElem* newElem = new TElem[2 * cp];
	int* newUrm = new int[2 * cp];
	int i;
	for (i = 0; i < cp; i++)
	{
		newElem[i] = elems[i];
		newUrm[i] = urm[i];
	}
	while (i < 2 * cp) {
		newElem[i] = { INT_MIN,NULL_TVALOARE };
		newUrm[i] = -1;
		i++;
	}
	cp *= 2;
	delete[] elems;
	delete[] urm;
	elems = newElem;
	urm = newUrm;
	actPrimLiber();

}// theta( 2*M) M dimensiunea tabelei 


int DO::d(TCheie e) const
{
	return abs(e) % 10;
}//theta(1)

void DO::actPrimLiber() {
	primLiber = 0;
	while (primLiber < cp && elems[primLiber].first != INT_MIN)
		primLiber++;
}//O(M)  M dimensiunea tabelei 


DO::DO(Relatie r) : r{ r } {
	elems = new TElem[MMAX];
	urm = new int[MMAX];
	cp = 10;
	for (int i = 0; i < MMAX; i++) {
		urm[i] = -1;
		elems[i].first = INT_MIN;
		elems[i].second = NULL_TVALOARE;
	}
	primLiber = 0;
	size = 0;
}// Theta(1)

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	int i = d(c);
	TElem e = make_pair(c, v);

	if (elems[i].first == INT_MIN)
	{
		elems[i] = e;
		if (i == primLiber)
			actPrimLiber();
		this->size++;
	}
	else {
		int j = -1;
		while (i != -1 && elems[i].first != c) {
			j = i;
			i = urm[i];
		}
		if (i != -1) {
			// am mai gasit cheia
			TValoare aux = elems[i].second;
			elems[i].second = v;
			return aux;
		}
		else {
			this->size++;
			if (primLiber < cp) {
				elems[primLiber] = e;
				urm[j] = primLiber;
				actPrimLiber();
			}
			else {
				redim();
				elems[primLiber] = e;
				urm[j] = primLiber;
				actPrimLiber();

			}
		}
	}

	return NULL_TVALOARE;
}// O(M)  M dimensiunea tabelei  dar in ipoteza dispersiei uniforme simple Theta(1)

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {

	int i = d(c);
	while (i != -1)
	{
		if (elems[i].first == c)
			return elems[i].second;
		i = urm[i];
	}
	return NULL_TVALOARE;
}// O(M) , dar in ipoteza dispersiei uniforme simple Theta(1)


//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	TValoare  v;
	int i = d(c);
	int j = -1;
	int k = 0; 
	while (urm[k] != i && k < cp)
		k++;
	if (k != cp)
		j = k;
	while (i != -1 && elems[i].first != c) {
		j = i;
		i = urm[i];

	}
	if (i == -1)
		return NULL_TVALOARE;
	v = elems[i].second;
	bool found = false;
	do {
		int p = urm[i];
		int pp = i;
		while (p != -1 && d(elems[p].first) != i) {
			pp = p;
			p = urm[p];
		}
		if (p == -1)
			found = true;
		else {
			elems[i] = elems[p];
			i = p;
			j = pp;
		}
	} while (!found);
	if (j != -1)
		urm[j] = urm[i];
	urm[i] = -1;
	elems[i] = { INT_MIN, NULL_TVALOARE };
	if (primLiber > i)
		primLiber = i;
	size--;
	return v;
} // O(M) M dimensiunea tabelei  dar in ipoteza dispersiei uniforme simple Theta(1)

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	
	return size;
}//theta(1)

//verifica daca dictionarul e vid
bool DO::vid() const {
	return (size == 0);
}//theta(1)

Iterator DO::iterator() const {
	return  Iterator(*this);
}// O(max(M, NlogN)


vector<TValoare> DO::colectiaValorilor() const
{
	/* Caz favoarbil = caz defavorabil = caz mediu, // O(max(M, NlogN); M = capacitatea tabelei
																		N - nr de elemente din dicitonar */
	/*
	* sublag colectiaValorilor(DO, v) 
	*							// pre-  DO - dictionar ordonat
	*							// post- v - vector de valori
		creeaza(v) 
	*   iterator(DO, it)
	*   prim(it)
	*	cat timp (valid(it)) executa
	*       TElement = it.element();
	*		adauga(v,TElement.v)
	*		it.urmator()
	*	sf cat timp
	*/
	vector < TValoare > v;
	Iterator it = this->iterator();
	it.prim();
	while(it.valid())
	{
		TElem e = it.element();
		v.push_back(e.second);
		it.urmator();
	}
	return v;

}




DO::~DO() {
	delete[] elems;
	delete[] urm;
}//theta(1)
