#ifndef BRKGA_H
#define BRKGA_H

#include "parameters.h"
#include "population.h"
#include "evolver.h"
#include "initializer.h"
#include "decoder.h"
#include "CLSD/clsddecoder.h"

namespace BRKGA {

class BRKGA {
public:
  BRKGA(Parameters* p, Initializer* i, CLSDdecoder* d)
    : pop(p->nrChromosomes(), p->nrGenes())
    , evo(p, &pop, i)
    , param(p)
    , init(i)
    , clsd(d)
  {}

  void run() {
    //initialize population with initializer
    init->randomInt(pop.begin(), pop.end());
    //decode initial pop ang get objectives
    auto objectives = decoder.decodeInitialPopulation(&pop, param, clsd);
    auto objIt = objectives.begin();
    //set objectives as fitness
    for (auto it = pop.beginFitness(); it != pop.endFitness(); ++it){
      it->second = *objIt;
       ++objIt;
    }
    //evolve pop
    evo.evolve();

    //all other gens
    for (int i = 0; i < param->maxGen(); ++i){
      auto objectives = decoder.decodePopulation(&pop, param, clsd);
      auto objIt = objectives.begin();
      for (auto it = pop.beginFitness()+param->nrElites(); it != pop.endFitness(); ++it){
        it->second = *objIt;
        ++objIt;
      }
      evo.evolve();
      std::cout << "Gen: " << i+1 << " Fit: " << pop.beginFitness()->second << "\n\n";
    }
  }

private:
  Decoder decoder;
  Population pop;
  Evolver evo;

  Parameters* param;
  Initializer* init;
  CLSDdecoder* clsd;


};

}
#endif // BRKGA_H
