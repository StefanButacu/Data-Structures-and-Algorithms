#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h> 
// memory leak 

#include <iostream>
#include "TestScurt.h"
#include "TestExtins.h"
/*TAD Lista Ordonat (interfata cu TPozitie=Iterator) – reprezentare sub forma unei LSI cu 
elementele ordonate în raport cu o relatie de ordine 
*/
int main() {
   testAll();
   testAllExtins();
   std::cout << "Finished LI Tests!" << std::endl;
   _CrtDumpMemoryLeaks();
   return 0;
}