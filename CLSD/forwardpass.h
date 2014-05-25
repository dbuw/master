#ifndef FORWARDPASS_H_INCLUDED
#define FORWARDPASS_H_INCLUDED

class ForwardPass{
public:

  ForwardPass(Data* d, Variables* v, Sequence* s, Encoding* e)
  : data(d)
  , vars(v)
  , sequence(s)
  , enc(e)
  {}

  void run(){

      for (int t = 0; t < data->getT()-2; ++t){

      std::vector<std::tuple< Sequence::iterator,
                              Sequence::iterator,
                              int,
                              int >> moves;
        //get feasible moves
        if (sequence->begin(t) != sequence->end(t) &&
            sequence->begin(t)+1 != sequence->end(t)){
        for (auto it = sequence->begin(t); it != sequence->end(t)-1; ++it){
          auto next = sequence->nextSetup(it);
          if (next != it){
            if (vars->getI(it->j, it->t) > 0)
            {
              std::tuple< Sequence::iterator,
                          Sequence::iterator,
                          int,
                          int > m;

              moves.push_back( std::make_tuple(it, next, saving(it,next), maxQuantity(it,next) ));

            }
          }
        }
        }
        //sort by savings
        if (!moves.empty()){
          std::sort(moves.begin(), moves.end(),
          [&](std::tuple< Sequence::iterator,
                          Sequence::iterator,
                          int,
                          int > a,
              std::tuple< Sequence::iterator,
                          Sequence::iterator,
                          int,
                          int > b) {
          return std::get<2>(a) > std::get<2>(b);
          });
          if (std::get<2>(moves[0]) > 0){

            *std::get<1>(moves[0])->X +=  std::get<3>(moves[0]);
            *std::get<0>(moves[0])->X -=  std::get<3>(moves[0]);
            if (*std::get<0>(moves[0])->X == 0){
              sequence->erase(std::get<0>(moves[0]));
            }
            for ( auto t = std::get<0>(moves[0])->t;
                  t < std::get<1>(moves[0])->t; ++t){
              *vars->toI(std::get<1>(moves[0])->j, t) -= std::get<3>(moves[0]);
            }
          }
          }
        }

  }

  int maxQuantity(Sequence::iterator curr, Sequence::iterator next)
  {
    int minQ = *curr->X;
    for (auto t = (curr->t)+1; t < (next->t); ++t){
      if (vars->getI(curr->j, t) < minQ){
        minQ = vars->getI(curr->j, t);
      }
    }
    int capacityNext = idleCapacity(next->t);
    if (capacityNext/data->getP(curr->j) < minQ){
      minQ = capacityNext/data->getP(curr->j);
    }
    return minQ;
  }

  int saving(Sequence::iterator curr, Sequence::iterator next){
    return (maxQuantity(curr,next) * data->getH(curr->j) * (next->t - curr->t));
  }

  int idleCapacity(int t){
    int pSum{0};
    for(auto it = sequence->begin(t); it != sequence->end(t); ++it){
      pSum += *it->X * data->getP(it->j);
    }
    int sSum{0};
    //if there is no linkage
    if (sequence->begin(t) != sequence->begin()){
      sSum += data->getST((sequence->end(t-1)-1)->j,sequence->begin(t)->j);
    }
    auto itFirst = sequence->begin(t);
    auto itLast = sequence->begin(t+1);

    while (itFirst != sequence->end() && itLast != sequence->end()){
      if( (itFirst+1) != sequence->end())
      sSum += data->getST(itFirst->j, (itFirst+1)->j);
      ++itFirst;
    }

    return std::max(0, data->getC(t) - pSum - sSum);
  }

private:
  Data* data;
  Variables* vars;
  Sequence* sequence;
  Encoding* enc;
};

#endif // FORWARDPASS_H_INCLUDED
