#ifndef CHROMOSOMEDECODER_H_INCLUDED
#define CHROMOSOMEDECODER_H_INCLUDED

#include "data.h"
#include "variables.h"
#include "encoding.h"

class ChromosomeDecoder
{
public:
  ChromosomeDecoder(){};

  void initialSolution(){

    initialSetups();
    for (unsigned t = data->getT()-1; t > 0; --t){

      auto seq = initialSequence(t);

      auto cUsage = processingTimes(seq) + setupTimes(seq);

      auto oC = -1 * (data->getC(t) - cUsage);

      auto candidates = consecutiveSetups(t);

      if (oC > 0){
          shiftFraction(candidates,t,&oC);
      }

      if (oC > 0){
          shiftEntireLot(candidates,t,&oC);
      }

      candidates = seq;

      if (oC > 0){
          shiftFraction(candidates,t,&oC);
      }

      if (oC > 0){
          shiftEntireLot(candidates,t,&oC);
      }

    }
  }

  std::vector<int> initialSetups(){
    return std::vector<int> (data->dBegin(), data->dEnd());
  }

  std::vector<unsigned> initialSequence(int t){
    auto prio = enc->sortedSequencePriorities(t);
    std::vector<unsigned> seq;
    for (auto i : prio){
      if(vars.getX(i,t) > 0){
        seq.push_back(vars.getX(i,t));
      }
    }
    return seq;
  }
  //sum of processing times in a sequence of items
  int processingTimes(const std::vector<unsigned>& seq){
    int pSum = 0;
    for (auto i : seq){
      pSum +=  data->getP(i); //processing times
    }
    return pSum;
  }
  //sum of setup times in a sequence of items
  int setupTimes(const std::vector<unsigned>& seq){
    int sSum = 0;
    for (auto it = seq.begin(); it != seq.end()-1; ++it){
      sSum += data->getSC(*it, *(it+1));
    }
    return sSum;
  }

  std::vector<unsigned> consecutiveSetups(int t){
    auto prio = enc->sortedSetupPriorities(t);
    std::vector<unsigned> candidates;
    for (auto i : prio){
      if (vars.getX(i,t) > 0 && vars.getX(i,t-1) > 0)
      candidates.push_back(i);
    }
    return candidates;
  }

  void shiftFraction(const std::vector<unsigned>& candidates, int t, int* oC){
    for (auto i : candidates){
      if (vars.getX(i,t) >= *oC){
        vars.setX(i,t, vars.getX(i,t) - *oC/data->getP(i));
        vars.setX(i,t-1, vars.getX(i,t-1) + *oC/data->getP(i));
        *oC = 0;
        return;
      }
    }
  }

  void shiftEntireLot(const std::vector<unsigned>& candidates, int t, int* oC){
    for (auto i : candidates){
      if (vars.getX(i,t) < *oC){
        vars.setX(i,t-1, vars.getX(i,t-1) + vars.getX(i,t));
        *oC -= vars.getX(i,t)*data->getP(i);
        vars.setX(i,t, 0);
      }
    }
  }

  void removeFromSequence(std::vector<unsigned>* seq, unsigned j){
    for (auto it = seq->begin(); it != seq->end(); ++it){
      if (*it == j)
        seq->erase(it);
    }
  }

  void addToSequence(std::vector<unsigned>* seq, unsigned j, int t){
    auto prio = enc->sortedSequencePriorities(t);
    auto curr = std::find(prio.begin(), prio.end(), j);
    for (auto it = curr-1; it == prio.begin(); --it){
        if (std::binary_search(seq->begin(), seq->end(), j)){
          seq->insert(it+1, j);
        }
    }
  }
private:
  Encoding* enc;
  Data* data;
  Variables vars;

};

#endif // CHROMOSOMEDECODER_H_INCLUDED
