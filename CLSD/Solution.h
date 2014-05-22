#ifndef SOLUTION_H_INCLUDED
#define SOLUTION_H_INCLUDED

#include "data.h"
#include "variables.h"
#include "encoding.h"
#include "sequence.h"

#include "InitialSequencer.h"
#include "Repair.h"
#include "backwardpass.h"
#include "forwardpass.h"
#include "fixlinks.h"

class Solution
{

public:
  Solution(Data* d, Encoding* e)
  : data(d)
  , enc(e)
  , vars(d->getJ(), d->getT())
  , sequence()
  {}

  int run()
  {

    InitialSequencer i(data,&vars,&sequence,enc);
    i.run();

    Repair r(data,&vars,&sequence,enc);
    r.run();

    BackwardPass b(data,&vars,&sequence,enc);
    b.run();

    generateInventory();
    ForwardPass f(data,&vars,&sequence,enc);
    f.run();

    FixLinks l(data,&vars,&sequence,enc);
    l.run();
    //fix
    r.run();

//    for (auto i : sequence){
//      std::cout << "(" << i.j << "," << i.t << "," << *i.X << ") ";
//    }
//    std::cout << "production \n";
//    for (int i = 0; i < data->getJ(); ++i){
//      for (int j = 0; j < data->getT(); ++j){
//        std::cout << vars.getX(i,j) << " ";
//      }
//      std::cout << "\n";
//    }
//    std::cout << "demand \n";
//    for (int i = 0; i < data->getJ(); ++i){
//      for (int j = 0; j < data->getT(); ++j){
//        std::cout << data->getD(i,j) << " ";
//      }
//      std::cout << "\n";
//    }

    generateInventory();
    auto obj = objective();

//    std::cout << "inventory\n";
//    for (int i = 0; i < data->getJ(); ++i){
//      for (int j = 0; j < data->getT(); ++j){
//        std::cout << vars.getI(i,j) << " ";
//      }
//      std::cout << "\n";
//    }

    return obj;
  }

  int setupCost(){
    int sum{0};
    for (auto it = sequence.begin(); it != sequence.end()-1; ++it){
      sum += data->getSC(it->j, (it+1)->j);
    }

    return sum;
  }

  int holdingCost(){
    int sum{0};
    for (auto i = 0; i < data->getJ(); ++i){
      for (auto j = 0; j < data->getT(); ++j){
        sum += vars.getI(i,j) * data->getH(i);
      }
    }
    return sum;
  }

  int backOrderCost()
  {
    int bc = 10000;
    int sum{0};
    for (auto i = 0; i < data->getJ(); ++i){
      for (auto j = 0; j < data->getT(); ++j){
        if (data->getD(i,j) > 0){
        if ( int(vars.getX(i,j) + vars.getI(i,j-1)) < data->getD(i,j)){
          sum += bc;
//          std::cout << "i,t " << i << " "<< j << " " << int(vars.getX(i,j) + vars.getI(i,j-1))
//          << " < " << data->getD(i,j) << " --- ";
        }

        }
      }
    }

    return sum;
  }
  void generateInventory(){
    for (auto i = 0; i < data->getJ(); ++i){
      vars.setI( i,0, std::max(0, vars.getX(i,0) - data->getD(i,0) ));

      for (auto j = 1; j < data->getT(); ++j){
          vars.setI( i,j,
                    std::max(0,
                             vars.getX(i,j) + vars.getI(i,j-1) - data->getD(i,j)));
      }
    }
  }

  int objective(){
    return (setupCost() + holdingCost() + backOrderCost());
  }


private:
  Data* data;
  Encoding* enc;
  Variables vars;
  Sequence sequence;

};

#endif // SOLUTION_H_INCLUDED
