#include "Iterator.h"
#include "LO.h"

#include <iostream>
using namespace std;

#include <exception>


void LO::redim(int cp) {
	TElement* newElems = new TElement[cp];
	int* newUrm = new int[cp];
	for (int i = 0; i < this->cp; i++) {
		newElems[i] = this->elems[i];
		newUrm[i] = this->urm[i];
	}
	for (int i = this->cp; i < cp - 1; i++)
		newUrm[i] = i + 1;
	newUrm[cp - 1] = -1;
	delete[] this->elems;
	delete[] this->urm;////

	elems = newElems;
	urm = newUrm;
	primLiber = this->cp;
	this->cp = cp;
} // theta(N)

int LO::aloca()
{    //se sterge primul element din lista spatiului liber
	if (this->primLiber == -1)
		redim(2 * this->cp);
	int i = this->primLiber;
	this->primLiber = this->urm[this->primLiber];
	return i;
} // theta(1)

void LO::dealoca(int i) {
	this->urm[i] = primLiber;
	this->primLiber = i;
}//theta(1)
void LO::initSpatiuLiber(int cp)
{
	for (int i = 0; i < cp-1; i++)
		this->urm[i] = i + 1;
	this->urm[cp-1] = -1;
} // theta(1)

LO::LO(Relatie r) {
	/* de adaugat */
	this->r = r;
	this->cp = 5; // 10
	this->sizeL = 0;
	this->head = NULL_TELEMENT;
	this->elems = new TElement [this->cp];
	this->urm = new int [this->cp];
	this->primLiber = 0;

	this->initSpatiuLiber(this->cp);
}//Theta(1)

// returnare dimensiune
int LO::dim() const {
	return this->sizeL;
}//thet(1)

// verifica daca LO e vida
bool LO::vida() const {
	
	return sizeL == 0;
}//theta(1)

// prima pozitie din LO
Iterator LO::prim() const {
	/* de adaugat */
	return Iterator(*this);
}//theta(1)

// returnare element de pe pozitia curenta
//arunca exceptie daca poz nu e valid
TElement LO::element(Iterator poz) const {
	/* de adaugat */
	if (!poz.valid())
		throw std::exception();
	return elems[poz.curent];
}//theta(1)


//sterge element de pe o pozitie poz si returneaza elementul sters
//dupa stergere poz e pozitionat pe elementul de dupa cel sters
//arunca exceptie daca poz nu e valid
TElement LO::sterge(Iterator& poz) {
	/* de adaugat */
	if (!poz.valid())
		throw std::exception();
	sizeL--;
	
	if (poz.curent == head) {
		TElement e = this->elems[poz.curent];
		int urm = this->urm[poz.curent];
		dealoca(poz.curent);
		head = urm;
		poz.curent = urm;
		return e;
	}
	else
	{
		int curent = head;
		int prev = -1;
		while (curent != poz.curent)
		{
			prev = curent;
			curent = urm[curent];
		}
		urm[prev] = urm[curent];
		TElement e = elems[curent];
		poz.urmator();
		dealoca(curent);
		return e;

	}
}// O(N)


// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
Iterator LO::cauta(TElement e) const {
	/* de adaugat */
	Iterator it = this->prim();
	// Iterator it(*this)
	  /// 1  4  6 10 
	while (it.valid() && r(elems[it.curent],e)) {
		if (elems[it.curent] == e)
			break;
		it.urmator();
		
	}
	if (it.valid() && elems[it.curent] == e)
		return it;
	else
	{
		while (it.valid()) 
			it.urmator();
		return it;
	}

}//O(n)

// adaugare element in LO
void LO::adauga(TElement e) {
	/* de adaugat */
	int i = creeazaNod(e);
	/*if(i == -1)
		 redim(2 * this->cp);
	*/
	if (i != -1) 
	{
		if (sizeL == 0) {
			// primul element 
			head = i;
			urm[i] = -1; // dupa el nu mai urmeaza nimic 
		}
		else {
			// trebuie inserat undeva prin interior 
			int curent = head;
			int prev = -1;
			while (curent != -1 && r(elems[curent], e))
			{
				prev = curent;
				curent = urm[curent];
			}
			if (curent != -1) {
				if (prev == -1) {
					// inserez inaintea primului element din lista 
					urm[i] = head;
					head = i;
				}
				else {
					urm[i] = urm[prev];
					urm[prev] = i;
				}
			}
			else {
				// curent = -1 fie daca trebuie la final
				if (prev == -1) {
					// trebuie pus inainte 
					urm[i] = head;
					head = i;
				}
				else {
					urm[i] = urm[prev];
					urm[prev] = i;
				}

			}
		}
	}
	sizeL++;
}//O(n)


int LO::creeazaNod(TElement e) {
	int i = aloca();
	this->elems[i] = e;
	urm[i] = -1;
	return i;
}//theta(1)

//destructor
LO::~LO() {
	/* de adaugat */
	delete[] elems;
	delete[] urm;
}//theta(1)

void LO::printLO() {
	for (int i = 0; i < this->cp; i++)
		cout << i << ' ';
	cout << endl;
	for (int i = 0; i < this->cp; i++)
		cout << elems[i] << ' ';
	cout << endl;
	for (int i = 0; i < this->cp; i++)
		cout << urm[i] << ' ';
	cout << endl;

}



Iterator LO::ultimulIndex(TElement elem) const
{
	/* Caz favorabil: Elementul nu se afla in multime -> Theta(1)
	Caz nefavorabil: Elementul se afla pe ultima pozitie -> Theta(N)
	Caz mediu: Elementul se afla oriunde in lista -> Theta(N)
	Complexitate totala O(N)
	*/
	
	/*it <- Cauta(lo, elem)
	* Daca !valid(it) atunci 
	*	returneaza it;
	* sf daca
	* LastIt <- Cauta(lo, elem)
	* urmator(it)
	* cat timp( valid(it) && valid(lastIT) && elems[it.curent] == elem ) executa
	* urmator(lastIT)
	* urmator(it)
	* sf cat timp
	* returneaza lastIT
	*/
	Iterator it = this->cauta(elem);
	if (!it.valid())
		return it;
	Iterator lastIt = this->cauta(elem);
	it.urmator();
	while (it.valid() && lastIt.valid() && elems[it.curent] == elem) {
		lastIt.urmator();
		it.urmator();
	}
	return lastIt;

}
