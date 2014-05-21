#ifndef AMENDINGPROCEDURE_H_INCLUDED
#define AMENDINGPROCEDURE_H_INCLUDED

#include "sequence.h"
#include "data.h"
#include "variables.h"

class AmendingProcedure
{
public:
  void run();




private:


  int overCapacity(int t){
    return std::max( 0, (capacityUsage(seq->begin(t),seq->end(t)) - data->getC(t)) );
  }

  int capacityUsage(Sequence::iterator first, Sequence::iterator last){
    return processingTimes(first,last) + setupTimes(first,last);
  }

  int processingTimes(Sequence::iterator first, Sequence::iterator last){
    int pSum = 0;
    while(first != last){
      pSum += first->X * data->getP(first->j);
    }
    return pSum;
  }
  int setupTimes(Sequence::iterator first, Sequence::iterator last){
    int sSum = 0;
    if (first == last){return sSum;}
    while(first != last-1){
      sSum += data->getST(first->j, (first+1)->j);
    }
    return sSum;
  }
private:
  Sequence* seq;
  Variables* vars;
  Data* data;
  Encoding* enc;

};

#endif // AMENDINGPROCEDURE_H_INCLUDED
