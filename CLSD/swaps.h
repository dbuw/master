#ifndef SWAPS_H_INCLUDED
#define SWAPS_H_INCLUDED

#include "sequenceutil.h"
class Swaps
{
public:
  Swaps(Data* d, Variables* v, Sequence* s, Encoding* e)
  : data(d)
  , vars(v)
  , sequence(s)
  , enc(e)
  {}

  void ThreeSwap()
  {
    for (int t = 0; t < data->getT(); ++t){
      if( std::distance(sequence->begin(t), sequence->end(t)) > 2){
        for (auto it = sequence->begin(t); it != sequence->end(t)-2; ++it){
          int idleC = idleCapacity(t);
          int bestSC;
          std::vector<int> bestPermutation;

          std::vector<Sequence::Operation*> items {&it, &it+1, &it+2};
          do
          {
            int sC = data->getSC(items[0], items{})
            int sT =
          }
          while(std::next_permutation(items.begin(), items.end()));
        }
      }
    }
  }

  void TwoSwap()
  {
    for (int t = 0; t < data->getT(); ++t){
      if( std::distance(sequence->begin(t), sequence->end(t)) > 2){
        for (auto it = sequence->begin(t); it != sequence->end(t)-1; ++it){
          int idleC = idleCapacity(t);
          int currST = 0;
          int currSC = 0;
          int swapST = 0;
          int swapSC = 0;
          if (it != sequence->end()){
            currST += data->getST( it->j, (it+1)->j );
            currSC += data->getSC( it->j, (it+1)->j );
            swapST += data->getST( (it+1)->j, it->j );
            swapSC += data->getSC( (it+1)->j, it->j );
          }
          if (it != sequence->begin(t)){
            currST += data->getST( (it-1)->j, it->j );
            currSC += data->getSC( (it-1)->j, it->j );
            swapST += data->getST( (it-1)->j, (it+1)->j );
            swapSC += data->getSC( (it-1)->j, (it+1)->j );
          }
//          std::cout << "idle capacity: " << idleC << "\n";
//          std::cout << swapSC << " < " << currSC << "\n";
//          std::cout << swapST << " < " << currST << "\n";
          if (swapSC < currSC && (idleC + currST - swapST) > 0){

            std::swap(*it, *(it+1));
          }
        }
      }
    }
  }
  int idleCapacity(int t){
    return data->getC(t) -
    productionTimes(sequence->begin(t), sequence->end(t), data) -
    setupTimes(sequence->begin(t), sequence->end(t), data);
  }

private:
  Data* data;
  Variables* vars;
  Sequence* sequence;
  Encoding* enc;
};

#endif // SWAPS_H_INCLUDED
