#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

DO::DO(Relatie r) : r{ r } {
	rad = nullptr;
	size = 0;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga_rec(Nod*& p, TElem e) {
	if (p == nullptr) {
		p = new Nod(e);
		p->st = p->dr = nullptr;
		size++;
		return NULL_TVALOARE;
	}
	else {
		if (p->elem.first == e.first) {
			TValoare aux = p->elem.second;
			p->elem.second = e.second;
			return aux;
		}
		if (r(e.first, p->elem.first)) 
			return adauga_rec(p->st,e);
		
		else 
			return adauga_rec(p->dr, e);
		
	}
}
TValoare DO::adauga(TCheie c, TValoare v) {
	
	return adauga_rec(rad, { c,v });;
} // O(H) - H inaltimea arborelui

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	/* de adaugat */
	Nod* p = cauta_rec(rad, c);
	if (p == nullptr) {
		return NULL_TVALOARE;
	}
	return p->elem.second;
} // O(H)


Nod* DO::sterge_rec(Nod* p, TCheie c) {
	if (p == nullptr) {
		return nullptr;
	}
	if (p->elem.first == c) {
		if (p->st != nullptr && p->dr != nullptr) {
			// nodul are subarbore stang si subarbore drept
			auto temp = minim(p->dr);
			p->elem = temp->elem;
			p->dr = sterge_rec(p->dr, temp->elem.first); // trb sters nodul temp
			return p;
		}
		else {
			Nod* temp = p;
			Nod* repl;
			if (p->st == nullptr)
				repl = p->dr;
			else
				repl = p->st;
			delete temp;
			return repl;
		}
	}

	if (r(c, p->elem.first)) {
		p->st = sterge_rec(p->st, c);
		return p;
	}
	else {
		if (!r(c, p->elem.first)) {
			p->dr = sterge_rec(p->dr, c);
			return p;
		}
		
	}

} // O(H)
// se returneaza adresa nodului avand cheia minima din subarborele de radacina p
Nod* DO::minim(Nod* p)
{
	if (p == nullptr)
		return nullptr;
	while (p->st != nullptr)
		p = p->st;
	return p;
}// O(H) 
//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	
	TValoare v = cauta(c);
	if (v == NULL_TVALOARE)
		return v;
	rad = sterge_rec(rad, c);
	size--;
	return v;
}// O(H)

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	return size;
} // theta(1)

//verifica daca dictionarul e vid
bool DO::vid() const {
	return size == 0;
} // theta(1)

Iterator DO::iterator() const {
	return  Iterator(*this);
}// theta(1)


DO::~DO() {
	distruge_rec(rad);
} // O(H)


void DO::distruge_rec(Nod* p)
{
	if (p != nullptr) {
		distruge_rec(p->st);
		distruge_rec(p->dr);
		delete p;
	}
}

Nod* DO::cauta_rec(Nod* p, TCheie val) const
{
	if (p == nullptr)
		return p;
	if (p->elem.first == val)
		return p;
	if (!r(p->elem.first, val))   // [p].c > val
		return cauta_rec(p->st, val);  // val e in subarborele stang
	else
		return cauta_rec(p->dr, val);
}


/*
* caz favorabil = caz nefavorabil = caz mediu = O(N)
	
	
	Functie difVMM(DO)
	// DO dictionar ordonat
	daca size == 0 atunci
		diffVMM <- -1
	maxi = inf
	mini = -inf
	cautaMinMax(DO.rad, maxi, mini)
	diffVMM <- maxi - mini
SfFunctie 


	subalgoritm cautaMinMax(p, maxi, mini)
	// pre p: *Nod 
	// post: maxi - valoarea maxima
	//       mini - valoarea minima
	
	daca p = NIL atunci
		Sf Subalgoritm
	daca [p].v > maxi atunci
		maxi <- [p].v
	daca [p].v < mini atunci
		mini <- [p].v
	cautaMinMax([p].st, maxi, mini)
	cautaMinMax([p].dr, maxi, mini)

*/
int DO::diferentaValoareMaxMin() const
{
	if (size == 0)
		return -1;
	int maxi = INT_MIN;
	int mini = INT_MAX;
	cautaMinMax(rad, maxi, mini);
	return maxi - mini;
}

void DO::cautaMinMax(Nod* p, int& maxi, int& mini) const {
	if (p == nullptr)
		return;
	if (p->elem.second > maxi)
		maxi = p->elem.second;
	if (p->elem.second < mini)
		mini = p->elem.second;
	cautaMinMax(p->st, maxi, mini);
	cautaMinMax(p->dr, maxi, mini);

}
