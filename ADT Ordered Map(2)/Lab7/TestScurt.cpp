#include <assert.h>

#include "DO.h"
#include "Iterator.h"

#include <exception>
using namespace std;

bool relatie1(TCheie cheie1, TCheie cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}


void myTest() {
    DO dictOrd = DO(relatie1);
    assert(dictOrd.diferentaValoareMaxMin() == -1);
    dictOrd.adauga(1, 0);
    dictOrd.adauga(2, 10);
    dictOrd.adauga(-1, -10);
    dictOrd.adauga(5, 5);
    assert(dictOrd.diferentaValoareMaxMin() == 20);
    dictOrd.adauga(10, 100);
    assert(dictOrd.diferentaValoareMaxMin() == 110);

}
void testAll() {
    myTest();
    DO dictOrd = DO(relatie1);
    assert(dictOrd.dim() == 0);
    assert(dictOrd.vid());
    dictOrd.adauga(1, 2);
    assert(dictOrd.dim() == 1);
    assert(!dictOrd.vid());
    assert(dictOrd.cauta(1) != NULL_TVALOARE);
    TValoare v = dictOrd.adauga(1, 3);
    assert(v == 2);
    assert(dictOrd.cauta(1) == 3);
    Iterator it = dictOrd.iterator();
    it.prim();
    while (it.valid()) {
        TElem e = it.element();
        assert(e.second != NULL_TVALOARE);
        it.urmator();
    }
    assert(dictOrd.sterge(1) == 3);
    assert(dictOrd.vid());
}

