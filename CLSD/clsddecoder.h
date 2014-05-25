#ifndef CLSDDECODER_H
#define CLSDDECODER_H

#include "data.h"
#include "Solution.h"
#include "encoding.h"

class CLSDdecoder
{
  public:

    CLSDdecoder(Data d)
    : data(d)
    {
      bestObjective = 100000000;
    }

    void init()
    {
        solutions.clear();
        encodings.clear();
    }

    std::vector<int> decode(){
      addSolutions();
      for(auto& i : solutions){
          i.run();
      }
      std::vector<int> objectives;

      for(auto& i : solutions){
          if (i.objective() < bestObjective){
            bestSolution = i;

            bestObjective = i.objective();
          }
          objectives.push_back(i.objective());

      }
      return objectives;
    }

    void addSolutions(){
      for (auto& i : encodings){
        Solution s(&data, &i);
        solutions.push_back(s);
      }
    }

    void addEncoding(std::vector<int> v){

      Encoding e(v, data.getJ(), data.getT());
      encodings.push_back(e);
    }

    void printBest(){
      bestSolution.print();
    }


  private:
    Solution bestSolution;

    int bestObjective;

    std::vector<Solution> solutions;
    std::vector<Encoding> encodings;
    Data data;

};

#endif // CLSDDECODER_H
