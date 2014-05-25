#ifndef INITIALSEQUENCER_H_INCLUDED
#define INITIALSEQUENCER_H_INCLUDED

#include "data.h"
#include "variables.h"
#include "encoding.h"
#include "sequence.h"
class InitialSequencer
{
public:
  InitialSequencer(Data* d, Variables* v, Sequence* s, Encoding* e)
  : data(d)
  , vars(v)
  , sequence(s)
  , enc(e)
  {}

  void run(){
    initProduction();
    constructSequence();
  }

  //initialize production with demand
  void initProduction()
  {
    vars->setX(data->getD());
  }

  void constructSequence()
  {
    //all periods
    for(int t = 0; t < data->getT(); ++t){
      //priorities
      auto seq = enc->sortedSequencePriorities(t);
      if (!sequence->empty()){
          //add last setup of t as first setup of period t+1
          sequence->push_back(constructOperation(((sequence->end()-1)->j),t));
          //delete first item from seq
          auto it = std::find(seq.begin(), seq.end(), (int) (sequence->end()-1)->j);
          if (it != seq.end())
            seq.erase(it);
      }
      //add all items with production to sequence
      for (auto i : seq){
        if (vars->getX((int) i, t) > 0){
          sequence->push_back(constructOperation(i,t));
        }
      }
    }
  }


  Sequence::Operation constructOperation(int i, int t){
      Sequence::Operation o;
      o.j = i;
      o.t = t;
      o.X = vars->toX(i, t);
      o.pSequence = enc->sequencePriority(i, t);
      o.pSetup = enc->setupPriority(i, t);
      return o;
  }

private:
  Data* data;
  Variables* vars;
  Sequence* sequence;
  Encoding* enc;
};

#endif // INITIALSEQUENCER_H_INCLUDED
