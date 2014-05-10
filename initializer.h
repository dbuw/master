#ifndef INITIALIZER_H_INCLUDED
#define INITIALIZER_H_INCLUDED

#include "random.h"
namespace BRKGA
{

class Initializer
{
  public:
  Initializer(Parameters* p){}

  template <typename Iter>
  void randomInt(Iter first, Iter last){
    if (first == last){return;};
    while (first != last){
      *first = uniformIntDistribution(param->minGeneValue(),
                                      param->maxGeneValue());
      ++first;
    }
  }
  private:
  Parameters* param;
};

}
#endif // INITIALIZER_H_INCLUDED
