#ifndef EVOLVER_H
#define EVOLVER_H

#include "population.h"
#include "parameters.h"
#include "initializer.h"
#include "random.h"
#include "util/util.h"
namespace BRKGA {


class Evolver {
public:
  Evolver(Parameters* pa, Population* po, Initializer* i)
    : param(pa)
    , pop(po)
    , tmppop((pa->nrOffspring()+pa->nrMutants())*pa->nrGenes())
    , init(i)
    {};

  void evolve() {
    sortFitness();
    createOffspring();
    createMutants();
    createNewPop();
  }

  void sortFitness() {
    std::sort(pop->beginFitness(), pop->endFitness(), sortFitLess());
  }


  void createOffspring() {
    //random numbers to choose a gene from parent one or two
    std::vector<int> r;
    for(int i = 0; i < param->nrOffspring()*param->nrGenes(); ++i) {
      r.push_back(uniformIntDistribution());
    }
    auto rIt = r.begin();
    auto tmpIt = tmppop.begin();

    for(int i = 0; i < param->nrOffspring(); ++i) { //no. of offspring
      //choose elite parent
      auto indexElite = uniformIntDistribution(0,param->nrElites()-1);
      //choose non-elite parent
      auto indexNonElite =  uniformIntDistribution(param->nrElites(), param->nrChromosomes()-1);
      //iterators to chosen parents
      auto eliteIt = pop->chromosomeBegin(indexElite);
      auto nonEliteIt = pop->chromosomeBegin(indexNonElite);
      //create offspring according to r and pc

      for(int j = 0; j < param->nrGenes(); ++j) { //no. of genes
        if(*rIt <= param->pC()) {
          *tmpIt = *eliteIt;
        } else {
          *tmpIt = *nonEliteIt;
        }
        ++rIt;
        ++tmpIt;
        ++eliteIt;
        ++nonEliteIt;
      }

    }
  }

  void createMutants() {
    auto itBegin = tmppop.begin()+param->nrOffspring()*param->nrGenes();
    auto itEnd = tmppop.end();
    init->randomInt(itBegin, itEnd);
  }

  void createNewPop() {
    auto tmpIt = tmppop.begin();
    //start at begin of first non-elite chromosome, iterate to begin of last
    //non-elite chromosome
    for(int i = param->nrElites(); i < param->nrChromosomes(); ++i) {
      //iterate over chromosome i
      for(auto it = pop->chromosomeBegin(i); it != pop->chromosomeEnd(i); ++it) {
        //copy gene of tmppop
        *it = *tmpIt;
        ++tmpIt;
      }
    }
  }

  //private:
  Parameters* param;
  Population* pop;
  std::vector<int> tmppop;
  Initializer* init;


};


}//namespace BRKGA
#endif // EVOLVER_H
