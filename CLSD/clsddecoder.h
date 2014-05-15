#ifndef CLSDDECODER_H
#define CLSDDECODER_H

#include "../population.h"

class CLSDdecoder
{
  public:
    CLSDdecoder(Population* p)
    : pop(p)
    {}
    void decodePopulation();
    void decodeChromosome();

  private:
    Population* pop;
    Data* data;
};

#endif // CLSDDECODER_H
