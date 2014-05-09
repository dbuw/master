#ifndef EVOLVER_H
#define EVOLVER_H

#include "population.h"
#include "parameters.h"
#include "util.h"

class Evolver
{
    public:
        Evolver();

    void sortFitness(){
      std::sort(pop->beginFitness(), pop->endFitness(), sortFitLess());
    }

    void createMutants(){


    }
    void createOffspring(){

    }

    private:
    Parameters* param;
    Population<int>* pop;
    Population<int> tmppop;


};



#endif // EVOLVER_H
