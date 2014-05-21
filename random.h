#ifndef RANDOM_H_INCLUDED
#define RANDOM_H_INCLUDED

#include <chrono>
#include <random>
#include "parameters.h"
namespace BRKGA {

unsigned seed = 5489u;
//unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
std::mt19937 engine(seed);

int uniformIntDistribution(int minValue = 0, int maxValue = 10000)
{
  std::uniform_int_distribution<int> UID(minValue,maxValue);
  return UID(engine);
}

}


#endif // RANDOM_H_INCLUDED
