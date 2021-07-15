#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE INT_MIN

#include <utility>
#include "Nod.h"
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

class DO {
	friend class Iterator;
private:
	/* aici e reprezentarea */
	int size;
	Nod* rad;
	Relatie r;
	void distruge_rec(Nod* p);
	Nod* cauta_rec(Nod* p, TCheie val) const;
	TValoare adauga_rec(Nod*& p, TElem e);
	Nod* sterge_rec(Nod* p, TCheie c);
	Nod* minim(Nod* p);
	void cautaMinMax(Nod* p, int& maxi, int& mini) const;
public:

	// constructorul implicit al dictionarului
	DO(Relatie r);


	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;


	// se returneaza diferenta dintre valoarea minima si valoarea maxima
	int diferentaValoareMaxMin()const;

	// destructorul dictionarului
	~DO();

};
