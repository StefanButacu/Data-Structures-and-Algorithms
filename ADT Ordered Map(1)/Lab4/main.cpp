#include <iostream>
#include "TestScurt.h"
#include "TestExtins.h"

/*Să se implementeze în C++ un anumit container de date (TAD) folosind o anumită 
reprezentare (indicată) și o listă înlănțuită (LSI – lista simplu înlănțuită, LDI – lista dublu înlănțuită) 
ca structură de date, cu reprezentarea înlănțuirilor pe tablou dinamic. 
*/
/*
23. TAD Lista Ordonată(interfața cu TPozitie = Iterator) – reprezentare sub forma unei LSI cu
elementele ordonate în raport cu o relație de ordine R.
*/

int main() {
    testAll();
    testAllExtins();
    std::cout << "Finished LP Tests!" << std::endl;
}
