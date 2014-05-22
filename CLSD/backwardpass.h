#ifndef BACKWARDPASS_H_INCLUDED
#define BACKWARDPASS_H_INCLUDED

class BackwardPass{
public:

  BackwardPass(Data* d, Variables* v, Sequence* s, Encoding* e)
  : data(d)
  , vars(v)
  , sequence(s)
  , enc(e)
  {}

  void run(){
      for (int t = data->getT()-1; t > 0; --t){

      std::vector<std::tuple< Sequence::iterator,
                              Sequence::iterator,
                              int >> moves;
        //get feasible moves
        for (auto it = sequence->begin(t); it != sequence->end(t)-1; ++it){
          auto prev = sequence->prevSetup(it);
          if (prev != it){

            if (idleCapacity(prev->t) >= *it->X * data->getP(it->j)){

              std::tuple< Sequence::iterator,
                          Sequence::iterator,
                          int > m;

              moves.push_back( std::make_tuple(it, prev, saving(it,prev)));
            }
          }
        }
        //sort by savings
        if (!moves.empty()){
          std::sort(moves.begin(), moves.end(),
          [&](std::tuple< Sequence::iterator,
                          Sequence::iterator,
                          int > a,
              std::tuple< Sequence::iterator,
                          Sequence::iterator,
                          int > b) {
          return std::get<2>(a) > std::get<2>(b);
          });
          if (std::get<2>(moves[0]) > 0){
              //std::cout << std::get<2>(moves[0]) << "\n";
            *std::get<1>(moves[0])->X = *std::get<0>(moves[0])->X;
            sequence->erase(std::get<0>(moves[0]));
          }
        }

      }
    }


  int saving(Sequence::iterator curr, Sequence::iterator prev){
    return  ( data->getSC( (curr-1)->j, curr->j )
            + data->getSC( curr->j, (curr+1)->j) //saved setup cost
            - data->getSC( (curr-1)->j, (curr+1)->j ) //new setup cost
            - (curr->t - prev->t) * data->getH(curr->j) * *(curr->X) ); //new holding cost

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

#endif // BACKWARDPASS_H_INCLUDED
