#include <iostream>

#include "UnitTest++.h"
#include "test/populationtest.h"
#include "test/evolvertest.h"

#include "brkga.h"
#include "CLSD/chromosomedecoder.h"

using namespace BRKGA;

int main()
{
    //return UnitTest::RunAllTests();

    std::vector<int> p;
    int x = 10000000;
    p.reserve(x);
    for (int i = 0; i < x; ++i)
    {
      p.push_back(i);
    }
    return 0;
}


