#ifndef REPAIR_H_INCLUDED
#define REPAIR_H_INCLUDED

#include "data.h"
#include "variables.h"
#include "encoding.h"
#include "sequence.h"
class Repair {
public:
  Repair(Data* d, Variables* v, Sequence* s, Encoding* e)
    : data(d)
    , vars(v)
    , sequence(s)
    , enc(e)
  {}

  //check if the same item is set up in period t and period t-1
  bool checkSetups(const std::vector<Sequence::Operation*>& operationsCurr,
                   const std::vector<Sequence::Operation*>& operationsPrev) {
    for(auto curr : operationsCurr) {
      for(auto prev : operationsPrev) {
        if(curr->j == prev->j) {
          return true;
        }
      }
    }
    return false;
  }

  bool checkFraction(const std::vector<Sequence::Operation*>& operationsCurr, int t) {
    for(auto curr : operationsCurr) {
      if(*curr->X*data->getP(curr->j) > overCapacity(t)) {
        return true;
      }
    }
    return false;
  }
  void ShiftFractionNoSetup(const std::vector<Sequence::Operation*>& operationsCurr,
                            const std::vector<Sequence::Operation*>& operationsPrev,
                            int t) {
    //try shifting without new setup
    for(auto curr : operationsCurr) {
      for(auto prev : operationsPrev) {
        int oC = overCapacity(t);
        if(curr->j == prev->j) {
          // (1) Shift FRACTION no new setup
          if(*curr->X * data->getP(curr->j) > oC
              && oC > 0) {
            *curr->X -= oC/data->getP(curr->j);
            *prev->X += oC/data->getP(curr->j);
          }
        }
      }
    }
  }

  void ShiftLotNoSetup(const std::vector<Sequence::Operation*>& operationsCurr,
                       const std::vector<Sequence::Operation*>& operationsPrev,
                       int t) {
    for(auto curr : operationsCurr) {
      for(auto prev : operationsPrev) {
        if(curr->j == prev->j) {
          // (2) Shift LOT no new setup
          if(*curr->X * data->getP(curr->j) <= overCapacity(t) &&
              *curr->X * data->getP(curr->j) > 0) {
            *prev->X += *curr->X;
            *curr->X = 0;
            return;
          }
        }
      }
    }
  }

  void shiftFractionSetup(const std::vector<Sequence::Operation*>& operationsCurr,
                          int t) {

    // (3) shift FRACTION with new setup
    int oC = overCapacity(t);
    for(auto curr : operationsCurr) {

      if(*curr->X * data->getP(curr->j) > oC) {

        auto o = createOperation(curr, oC);

        *curr->X -= oC/data->getP(curr->j);

        if(sequence->begin(t-1) == sequence->end(t-1)) {
          sequence->insert(sequence->begin(t), o);
        } else {
          auto it = sequence->begin(t-1);
          while(it->pSequence < o.pSequence && it != sequence->end(t-1)) {
            ++it;
          }
          sequence->insert(it,o);
        }
        return;
      }
    }
  }

  void shiftLotSetup(const std::vector<Sequence::Operation*>& operationsCurr,
                     int t) {

    int oC = overCapacity(t);
    for(auto curr : operationsCurr) {

      if(*curr->X * data->getP(curr->j) <= oC &&
         *curr->X * data->getP(curr->j) > 0) {

        auto o = createOperation(curr, *curr->X * data->getP(curr->j));

        *curr->X = 0;

        if(sequence->begin(t-1) == sequence->end(t-1)) {
          sequence->insert(sequence->begin(t), o);
        } else {
          auto it = sequence->begin(t-1);
          while(it->pSequence < o.pSequence && it != sequence->end(t-1)) {
            ++it;
          }
          sequence->insert(it,o);
        }
        return;
      }
    }

    // (4) shift LOT with new setup
//    int oC = overCapacity(t);
//    auto curr = operationsCurr.begin();
//    while(curr != operationsCurr.end() &&
//          *(*curr)->X * data->getP((*curr)->j) <= oC &&
//          *(*curr)->X * data->getP((*curr)->j) > 0) {
//      ++curr;
//    }
//
//    auto o = createOperation(*curr, *(*curr)->X /* *data->getP((*curr)->j)*/);
//
//    *(*curr)->X = 0;
//    for(auto it = sequence->begin(t); it != sequence->end(t); ++it) {
//      if(it->X == 0) {
//        it = sequence->erase(it);
//      }
//    }
//
//    if(sequence->begin(t-1) == sequence->end(t-1)) {
//      sequence->insert(sequence->begin(t), o);
//    }
//
//    else {
//      auto it = sequence->begin(t-1);
//      while(it->pSequence < o.pSequence && it != sequence->end(t-1)) {
//        ++it;
//      }
//      sequence->insert(it,o);
//    }

  }
  void run() {
    int t = data->getT()-1;
    while(t > 0) {
      while(overCapacity(t) > 0) {
        //get operations in t and t-1
        auto operationsCurr = getCandidatesCurr(t);
        auto operationsPrev = getCandidatesPrev(t);

        if(checkSetups(operationsCurr, operationsPrev)) {
          //try shifting without new setup
          ShiftFractionNoSetup(operationsCurr, operationsPrev, t);
          ShiftLotNoSetup(operationsCurr, operationsPrev, t);
          deleteOperation(t);
        }
        else {
          if(checkFraction(operationsCurr, t)) {
            shiftFractionSetup(operationsCurr, t);
          } else {
            shiftLotSetup(operationsCurr, t);
            deleteOperation(t);
          }
        }
//        std::cout << overCapacity(t) << "\n";
//        for (auto it = sequence->begin(t); it != sequence->end(t); ++it){
//          std::cout << "(" << it->j << "," << it->t << "," << *it->X <<") ";
//        }
//        std::cout << "\n";
     }
    --t;
    }
  }
    void deleteOperation(int t) {
    //delete operations if no production
    for (auto it = sequence->begin(t); it != sequence->end(t); ++it){
      if (*it->X == 0){
        sequence->erase(it);
        return;
      }
    }
  }



  std::vector<Sequence::Operation*> getCandidatesCurr(int t) {
    std::vector<Sequence::Operation*> operationsCurr;
    for(auto it = sequence->begin(t); it != sequence->end(t); ++it) {
      operationsCurr.push_back(&*it);
    }
    if(!operationsCurr.empty()) {
      operationsCurr.erase(operationsCurr.end()-1);
    }
    std::sort(operationsCurr.begin(), operationsCurr.end(),
    [&](Sequence::Operation* a, Sequence::Operation* b) {
      return a->pSetup < b->pSetup;
    });
    return operationsCurr;
  }

  std::vector<Sequence::Operation*> getCandidatesPrev(int t) {
    std::vector<Sequence::Operation*> operationsPrev;
    for(auto it = sequence->begin(t-1); it != sequence->end(t-1); ++it) {
      operationsPrev.push_back(&*it);
    }
    return operationsPrev;
  }

  Sequence::Operation createOperation(Sequence::Operation* curr, int capacity) {
    Sequence::Operation o;
    o.j = curr->j;
    o.t = curr->t - 1;
    vars->setX(o.j, o.t, capacity/data->getP(o.j));
    o.X = vars->toX(o.j, o.t);
    o.pSequence = enc->sequencePriority(o.j, o.t);
    o.pSetup = enc->sequencePriority(o.j, o.t);
    return o;
  }




  int overCapacity(int t) {
    return std::max(0, productionTimes(t) + setupTimes(t) - data->getC(t));
  }

  int productionTimes(int t) {
    int sum {0};
    for(auto it = sequence->begin(t); it != sequence->end(t); ++it) {
      sum += *(it->X) * data->getP(it->j);
    }

    return sum;
  }

  int setupTimes(int t) {
    int sum {0};
    //if there is no linkage
    if (sequence->begin(t) != sequence->begin()){
      sum += data->getST((sequence->end(t-1)-1)->j,sequence->begin(t)->j);
    }
    auto itFirst = sequence->begin(t);
    auto itLast = sequence->begin(t+1);

    while (itFirst != sequence->end() && itLast != sequence->end()){
      if( (itFirst+1) != sequence->end())
      sum += data->getST(itFirst->j, (itFirst+1)->j);
      ++itFirst;

    }



    return sum;
  }

private:
  Data* data;
  Variables* vars;
  Sequence* sequence;
  Encoding* enc;
};


#endif // REPAIR_H_INCLUDED
