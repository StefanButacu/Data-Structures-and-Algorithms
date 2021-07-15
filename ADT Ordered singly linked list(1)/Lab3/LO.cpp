#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>

LO::LO(Relatie r) {
	/* Theta(1) */
	this->r = r;
	primul = nullptr;
	ultimul = nullptr;
}

// returnare dimensiune
int LO::dim() const {

	/* Complexitate timp Theta(N), N nr de elemente */
	int N = 0;
	Nod* i = primul;
	while (i != nullptr) {
		N++;
		i = i->next;
	}
	return N;
}

// verifica daca LO e vida
bool LO::vida() const {
	/* Complexitate timp Theta(N), N nr de elemente */
	return dim() == 0;
}

// prima pozitie din LO
Iterator LO::prim() const {
	/* Theta(1) */
	return Iterator(*this);
}

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
	/* Theta(1) */
	if (!poz.valid())
		throw std::exception();
	return poz.element();
}

//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	/* complexitate timp O(N) ( exista cazuri favorabil, nefavorabil, mediu)  */
	if (!poz.valid())
		throw std::exception();

	TElement e = poz.element();
	
	Nod* pointer_sters = poz.p;
	
	if (poz.p == this->primul) {
		Nod* q = primul->next;
		primul = q;
	}
	else if(poz.p == this->ultimul){
		Nod* q = this->primul;
		while (q->next != this->ultimul)
			q = q->next;
		q->next = nullptr;
		this->ultimul = q;
	}
	else {
		Nod* q = this->primul;
		while (q->next != poz.p)
			q = q->next;
		q->next = (poz.p)->next;
		
	}
	poz.urmator();
	delete pointer_sters;
	pointer_sters = nullptr;
	return e;
}


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const {
	/* complexitate timp O(N) ( exista cazuri favorabil, nefavorabil, mediu) */
	Iterator p(*this);
	while (p.valid()) {
		if (p.element() == e)
			return p;
		p.urmator();
	}
	return p;
}

// adaugare element in LO
void LO::adauga(TElement e) {
	/* Complexitate timp - O(N)  ( din cauza ca poate fi inserat si undeva in interior)  
	*/
	if (this->primul == nullptr) {
		Nod* p = new Nod;
		p->val = e;
		p->next = nullptr;
		this->primul = this->ultimul = p;
		return;
	}  
	if (!r(primul->val, e)) {
		// inserez inaintea primului
		Nod* p = new Nod;
		p->val = e;
		p->next = primul;
		primul = p;
		return;
	}    
	// ultima valoare e mai mica decat ceea ce introduc
	if (r(ultimul->val, e)) {
		Nod* p = new Nod;
		p->val = e;
		p->next = nullptr;
		ultimul->next = p;
		ultimul = p;
		return;
	}
	else { // e undeva prin interior
		Nod* i = this->primul;
		while (i->next != nullptr && this->r(i->next->val, e))
			i = i->next;
		// urmatorul element dupa i NU mai este in relatie cu e 
		// dupa i trebuie sa inserez nodul nou
		Nod* p = new Nod;
		p->val = e;
		p->next = i->next;
		i->next = p;
		return;
	}
}


//destructor
void destroy(Nod* p) {
	if (p == nullptr)
		return;
	destroy(p->next);
	delete p;
	p = nullptr;
}
LO::~LO() {
	/* Theta(N) */

	destroy(this->primul);
}
