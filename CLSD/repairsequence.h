#ifndef REPAIRSEQUENCE_H_INCLUDED
#define REPAIRSEQUENCE_H_INCLUDED

#include "sequenceutil.h"

class RepairSequence {
public:
  RepairSequence(Data* d, Variables* v, Sequence* s, Encoding* e)
    : data(d)
    , vars(v)
    , sequence(s)
    , enc(e)
  {}

  void run()
  {

    //do backwards over all periods
    for (auto t = data->getT()-1; t > 0; --t){

      //while consumption exceeds capacity
      while(overConsumtion(t) > 0){

//        std::cout << overConsumtion(t) << "\n";
//        for (auto it = sequence->begin(t); it != sequence->end(t); ++it){
//          std::cout << "(" << it->j << "," << it->t << "," << *it->X <<") ";
//        }
//        std::cout << "\n";

        auto candidates = getNoSetupCandidates(t);

        int oC = overConsumtion(t);

        if (!candidates.empty()){
          shiftFractionNoSetup(t, overConsumtion(t));
          if (overConsumtion(t) > 0){
            shiftLotNoSetup(t, overConsumtion(t));
          }
        }

        if (overConsumtion(t) == oC)//no change so far
        {
          candidates = getSetupCandidates(t);
          shiftFractionSetup(t, overConsumtion(t));

          if (overConsumtion(t) == oC){//no change so far
            shiftLotSetup(t, overConsumtion(t));
          }
        }
//        std::cout << overConsumtion(t) << "\n";
//        for (auto it = sequence->begin(t); it != sequence->end(t); ++it){
//          std::cout << "(" << it->j << "," << it->t << "," << *it->X <<") ";
//        }
//        std::cout << "\n";
      }
    }
  }



  //a)
  void shiftFractionNoSetup(int t, int oC) {
    auto candidates = getNoSetupCandidates(t);
    sortSetupPriority(&candidates);
    auto it = candidates.begin();
    while(it != candidates.end() &&
          //not enough production to eliminate overconsumption
          (*(*it)->X * data->getP((*it)->j)) < oC) {
      ++it;
    }
    if(it != candidates.end()) {
      shift(*it, (oC / data->getP((*it)->j)));
    }
  }
  //b)
  void shiftLotNoSetup(int t, int oC) {
    auto candidates = getNoSetupCandidates(t);
    if (!candidates.empty())
      candidates.pop_back();
    auto it = minSetupPriority(&candidates);
    if(it != candidates.end()) {
      shift(*it, *(*it)->X);
    }
  }

  //c
  void shiftFractionSetup(int t, int oC) {
    auto candidates = getSetupCandidates(t);

    sortSetupPriority(&candidates);

    auto it = candidates.begin();

    while(it != candidates.end() &&
          //not enough production to eliminate overconsumption
          (*(*it)->X * data->getP((*it)->j)) < oC) {

      ++it;
    }
    if(it != candidates.end()) {

      //get iterator to operation which will be shifted and advance
      //since a new operation will be added, the new position of the item
      //will be +1
      auto sequenceIt = sequence->findOperation(**it);
      ++sequenceIt;

      addNewSetup(*it);
      shift(&*sequenceIt, (oC / data->getP((&*sequenceIt)->j)));
    }
  }
  //d)
  void shiftLotSetup(int t, int oC) {
    auto candidates = getSetupCandidates(t);

    auto it = minSetupPriority(&candidates);

    if(it != candidates.end()) {

      //get iterator to operation which will be shifted and advance
      //since a new operation will be added, the new position of the item
      //will be +1
      auto sequenceIt = sequence->findOperation(**it);
      ++sequenceIt;

      addNewSetup(*it);

      shift(&*sequenceIt, *(&*sequenceIt)->X);
    }
  }

//returns items with Xit > 0 and Xi,t-1 > 0
  std::vector<Sequence::Operation*> getNoSetupCandidates(int t) {
    std::vector<Sequence::Operation*> seq;
    for(auto it = sequence->begin(t); it != sequence->end(t); ++it) {
      if(vars->getX(it->j, it->t) > 0 &&
          vars->getX(it->j, it->t-1) > 0) {
        seq.push_back(&*it);
      }
    }
//    if(!seq.empty()) {
//      seq.pop_back();
//    }
    return seq;
  }

//returns items with Xit > 0 and Xi,t-1 = 0
  std::vector<Sequence::Operation*> getSetupCandidates(int t) {

    std::vector<Sequence::Operation*> seq;
    for(auto it = sequence->begin(t); it != sequence->end(t); ++it) {
      if(vars->getX(it->j, it->t) > 0 &&
          vars->getX(it->j, it->t-1) == 0) {
        seq.push_back(&*it);
      }
    }

//    if(!seq.empty()) {
//      seq.pop_back();
//    }
    return seq;
  }

//add a new setup for the same item o->j to the period o->t-1
  void
  addNewSetup(Sequence::Operation* o) {

    Sequence::Operation newO;
    newO.j = o->j;
    newO.t = o->t-1;
    newO.X = vars->toX(newO.j, newO.t);
    newO.pSequence = enc->sequencePriority(newO.j, newO.t);
    newO.pSetup = enc->setupPriority(newO.j, newO.t);
    sequence->insertOrdered(newO, newO.t);
  }
//returns an iterator to the element with the lowest priority
  std::vector<Sequence::Operation*>::iterator
  minSetupPriority(std::vector<Sequence::Operation*>* operations) {
    return std::min_element(operations->begin(), operations->end(),
    [&](Sequence::Operation* lhs, Sequence::Operation* rhs) {
      return (lhs->pSetup < rhs->pSetup);
    });
  }
//sorts pointers to operations in non-decreasing order of setup priority
  void sortSetupPriority(std::vector<Sequence::Operation*>* operations) {
    std::sort(operations->begin(), operations->end(),
    [&](Sequence::Operation* lhs, Sequence::Operation* rhs) {
      return (lhs->pSetup < rhs->pSetup);
    });
  }
//returns the amount productions and setups exceed the capacity
  int overConsumtion(int t) {
    if (t < data->getT()-1)
    return std::max(0, consumption(sequence->begin(t), sequence->end(t), data) - data->getC(t));
    return std::max(0, consumption(sequence->begin(t), sequence->end(t)-1, data) - data->getC(t));
  }
//shifts X production from item j in period t to item j in period t-1
//if the procution of j in t is 0 after the shift, this setup is deleted from
//the sequence
  void shift(Sequence::Operation* currOp, int X) {
    auto curr = sequence->findOperation(*currOp);
    auto prev = sequence->prevSetup(curr);
    *curr->X -= X;
    *prev->X += X;
    if(*curr->X == 0) {
      sequence->erase(curr);
    }
  }
private:
  Data* data;
  Variables* vars;
  Sequence* sequence;
  Encoding* enc;
};

#endif // REPAIRSEQUENCE_H_INCLUDED
