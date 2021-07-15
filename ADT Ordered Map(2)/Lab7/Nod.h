#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE INT_MIN
#define NULL_TCHEIE INT_MIN
#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Nod
{
public:
	TElem elem;
	Nod* st;
	Nod* dr;
	Nod() : elem{ NULL_TCHEIE, NULL_TVALOARE }, st{ nullptr }, dr{ nullptr } {};
	Nod(TElem e) : elem{ e }, st{ nullptr }, dr{ nullptr } {};
	Nod(TCheie c) : elem{ c, NULL_TVALOARE }, st{ nullptr }, dr{ nullptr }{};
	Nod(TCheie c, TValoare v) : elem{ c, v }, st{ nullptr }, dr{ nullptr }{};
};

