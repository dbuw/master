#ifndef DECODER_H_INCLUDED
#define DECODER_H_INCLUDED

#include "population.h"
#include "parameters.h"

#include "CLSD/clsddecoder.h"

namespace BRKGA
{

class Decoder {
public:


  std::vector<int> decodePopulation(Population* pop, Parameters* param, CLSDdecoder* d){
    return decodePop(pop,param,d, param->nrElites());
  }

  std::vector<int> decodeInitialPopulation(Population* pop, Parameters* param, CLSDdecoder* d){
    return decodePop(pop,param,d,0);
  }

  std::vector<int> decodePop(Population* pop, Parameters* param, CLSDdecoder* d, int i){
    d->init();
    for (; i < (int) pop->populationSize(); ++i){
        std::vector<int> e (pop->chromosomeBegin(i), pop->chromosomeEnd(i));
        d->addEncoding(e);
    }

    return d->decode();
  }


};

}
#endif // DECODER_H_INCLUDED
