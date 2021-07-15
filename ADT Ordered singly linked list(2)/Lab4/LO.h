#pragma once

class Iterator;

typedef int TComparabil;
typedef TComparabil TElement;

typedef bool (*Relatie)(TElement, TElement);

#define NULL_TELEMENT -1

class LO {
private:
	friend class Iterator;
private:
	/* aici reprezentarea */
	int cp;
	int head, primLiber;
	int sizeL;
	TElement* elems;
	int* urm;
	int aloca(); 
	void initSpatiuLiber(int cp);
	void dealoca(int i);
	int creeazaNod(TElement e);
	Relatie r;
	void redim(int cp);
public:
	// constructor
	LO(Relatie r);

	// returnare dimensiune
	int dim() const;

	// verifica daca LO e vida
	bool vida() const;

	// prima pozitie din LO
	Iterator prim() const;

	// returnare element de pe pozitia curenta
	//arunca exceptie daca poz nu e valid
	TElement element(Iterator poz) const;

	// adaugare element in LO a.i. sa se pastreze ordinea intre elemente
	void adauga(TElement e);

	// sterge element de pe o pozitie poz si returneaza elementul sters
	//dupa stergere poz e pozitionat pe elementul de dupa cel sters
	//arunca exceptie daca poz nu e valid
	TElement sterge(Iterator& poz);

	// cauta element si returneaza prima pozitie pe care apare (sau iterator invalid)
	Iterator cauta(TElement e) const;

	//destructor
	~LO();

	void printLO();
	/// returnează ultimul index al unui element dat
// daca elementul nu este în listă returnează un TPozitie nevalid
// TPozitie [nume_clasa]::ultimulIndex(TElem elem) const;
// Obs: depinzând dacă aveți listă indexată sau cu poziție iterator, 
	//înlocuiți TPozitie cu int sau IteratorListă și  TPozitie nevalid cu indexul - 1 sau iterator nevalid.

	Iterator ultimulIndex(TElement elem) const;
};
