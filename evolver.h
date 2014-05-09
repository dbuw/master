#ifndef EVOLVER_H
#define EVOLVER_H

#include "population.h"
#include "parameters.h"
#include "random.h"

class Evolver
{
    public:
        Evolver();

    void createMutants(){
        mutate(tmppop.chromosomeBegin(param->nrOffspring()),
               tmppop.end());

    }
    void createOffspring(){
        std::vector<int> r(param->nrOffspring()*param->nrGenes());
        for (auto it = r.begin(); it != r.end(); ++it){
            *it = rand->randomize();
        }
        auto oIt = tmppop.begin();
        while (oIt != tmppop.chromosomeEnd(param->nrOffspring*param->nrGenes())){

        }
    }

    private:
    Parameters* param;
    Population* pop;
    Population tmppop;
    Random* rand;


};


template <typename OutputIterator>
void randRange(OutputIterator first, OutputIterator last)
{
    while (first != last){
    //call random
    *first = rand->randomize();
    ++first;
    }
}

#endif // EVOLVER_H
