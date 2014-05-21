#ifndef INITIALSEQUENCER_H
#define INITIALSEQUENCER_H

class InitialSequencer
{
  public:
    InitialSequencer(Sequence* s, Data* d, Variables* v, Encoding* e)
    : seq(s)
    , data(d)
    , vars(v)
    , enc(e)
    {}

    void init();

  void run(){
      vars->setX(initialSetups());

      for(unsigned t = data->getT()-1; t != (size_t)-1; --t){

        auto seqT = initialSequence(t);

        if(t < (unsigned) data->getT()-1) {
          addLastSetup(&seqT, (seq->end()-1)->j);
        }

        for(auto rIt = seqT.rbegin(); rIt != seqT.rend(); ++rIt) {
          seq->push_back(*rIt,t,vars->getX(*rIt,t));
        }

      }
      seq->reverse();
  }

  std::vector<int> initialSetups() {
    return std::vector<int> (data->dBegin(), data->dEnd());
  }

  std::vector<unsigned> initialSequence(int t) {
    auto prio = enc->sortedSequencePriorities(t);
    std::vector<unsigned> seqT;
    for(auto i : prio) {
      if(vars->getX(i,t) > 0) {
        seqT.push_back(i);
      }
    }
    return seqT;
  }

  void addLastSetup(std::vector<unsigned>* seqT, unsigned j) {
    auto it = std::find(seqT->begin(),seqT->end(), j);
    if(it != seqT->end()) {
      seqT->erase(it);
    }
    seqT->push_back(j);
  }


  private:
    Sequence* seq;
    Data* data;
    Variables* vars;
    Encoding* enc;
};

#endif // INITIALSEQUENCER_H
