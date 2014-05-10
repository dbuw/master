#ifndef BRKGA_H
#define BRKGA_H

#include "parameters.h"
#include "population.h"
#include "evolver.h"
#include "initializer.h"
#include "decoder.h"

namespace BRKGA
{

class BRKGA
{
  public:
    BRKGA(Parameters* p, Initializer* i)
    : pop(p->nrChromosomes(), p->nrGenes())
    , evo(p, &pop)
    , param(p)
    , init(i)
    {}

    void run(){

    }

  private:
    Population pop;
    Evolver evo;
    Parameters* param;
    Initializer* init;


};

}
#endif // BRKGA_H
