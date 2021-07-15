#include <assert.h>

#include "LO.h"
#include "Iterator.h"
#include <iostream>
#include <exception>
using namespace std;

bool relatie1(TElement cheie1, TElement cheie2) {
    if (cheie1 <= cheie2) {
        return true;
    }
    else {
        return false;
    }
}

void myTest() {
    LO lo(relatie1);
    lo.adauga(10);
 
    lo.adauga(1);
 
    lo.adauga(11);

    lo.adauga(4);
   
    lo.adauga(15);

    lo.adauga(7);
    for (int i = 0; i < 80; i++)
        lo.adauga(i);
   
    Iterator it = lo.ultimulIndex(7);
    assert(it.element() == 7);
    it.urmator();
    assert(it.element() == 8);

    Iterator it2 = lo.ultimulIndex(80);
    assert(!it2.valid());
  
    Iterator it3 = lo.ultimulIndex(79);
    assert(it3.element() == 79);
}
void testAll() {
    myTest();
    LO lo = LO(relatie1);
    assert(lo.dim() == 0);
    assert(lo.vida());
    lo.adauga(1);
    assert(lo.dim() == 1);
    assert(!lo.vida());
    Iterator itCauta = lo.cauta(1);
    assert(itCauta.valid());
    assert(itCauta.element() == 1);
    itCauta.urmator();
    assert(!itCauta.valid());
    itCauta.prim();
    assert(itCauta.valid());
    Iterator itPrim = lo.prim();
    assert(itPrim.valid());
    assert(itPrim.element() == 1);
    assert(lo.sterge(itCauta) == 1);
    assert(lo.dim() == 0);
    assert(lo.vida());
}

