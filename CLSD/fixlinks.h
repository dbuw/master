#ifndef FIXLINKS_H_INCLUDED
#define FIXLINKS_H_INCLUDED

class FixLinks{
public:
  FixLinks(Data* d, Variables* v, Sequence* s, Encoding* e)
  : data(d)
  , vars(v)
  , sequence(s)
  , enc(e)
  {}

  void run()
  {
    for (int t = 1; t < data->getT()-1; ++t){
      if (*sequence->begin(t)->X == 0){
        auto candidates = getCandidates(t);
        if (!candidates.empty()){
          auto it = minSequencePriority(&candidates);

          auto a = sequence->begin(t);
          auto b = sequence->findOperation(**it);

          std::swap(*a, *b);
          sequence->erase(b);
        }
      }
    }
    for(auto it = sequence->begin(); it != sequence->end(); ++it){
      if (*it->X == 0){
        it = sequence->erase(it);
      }
    }
  }

  //returns items with Xit > 0 and Xi,t-1 > 0 and ait+1 = 0
  std::vector<Sequence::Operation*> getCandidates(int t) {
    std::vector<Sequence::Operation*> seq;
    for(auto it = sequence->begin(t); it != sequence->end(t); ++it) {
      if(vars->getX(it->j, it->t) > 0 &&
        vars->getX(it->j, it->t-1) > 0 &&
        sequence->begin(t+1)->j != it->j ) {
        seq.push_back(&*it);
      }
    }
    return seq;
  }

  std::vector<Sequence::Operation*>::iterator
  minSequencePriority(std::vector<Sequence::Operation*>* operations) {
    return std::min_element(operations->begin(), operations->end(),
    [&](Sequence::Operation* lhs, Sequence::Operation* rhs) {
      return (lhs->pSequence < rhs->pSequence);
    });
  }

private:
  Data* data;
  Variables* vars;
  Sequence* sequence;
  Encoding* enc;
};

#endif // FIXLINKS_H_INCLUDED
