#include "Iterator.h"
#include "DO.h"
#include <algorithm>
using namespace std;

Iterator::Iterator(const DO& d) : dict(d) {
	/* de adaugat */
	for (int i = 0; i < d.cp; i++)
		if (d.elems[i].first != INT_MIN) // cheie valida
			v.push_back(d.elems[i]);
	sort(v.begin(), v.end(), [&](TElem t1, TElem t2) {return dict.r(t1.first,t2.first); });
	curent = 0;
}// O(M) - M - capacitatea tabeleie + Theta(N log N) , N - nr de perechi 
// O(max(M, NlogN);

void Iterator::prim() {
	curent = 0;
}//theta(1)

void Iterator::urmator() {
	curent++;
}//theta(1);

bool Iterator::valid() const {
	return curent < v.size();
}//theta(1)

TElem Iterator::element() const {
	return v.at(curent);
}//theta(1)


