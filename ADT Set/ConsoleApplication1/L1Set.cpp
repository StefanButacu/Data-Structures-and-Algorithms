
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "TestExtins.h"
#include "TestScurt.h"
// 12. TAD Mulțime – reprezentare folosind un vector boolean(de biți).
int main()
{
    std::cout << "Hello World!\n";
    testAll();
    testAllExtins();
    _CrtDumpMemoryLeaks();
    return 0;
}
