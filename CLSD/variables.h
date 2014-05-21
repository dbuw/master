#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

#include "../util/util.h"

class Variables {
public:
  typedef std::vector<int> container;
  typedef container::const_iterator const_iterator;

  Variables()
  {}
  Variables(int j, int t)
    : J(j)
    , T(t)
    , X(j*t,0)
    , I(j*t,0)
  {}

  //setters
  void setNumberOfItems(int v) {J = v;}
  void setNumberOfPeriods(int v) {T = v;}
  void setX(int j, int t, int val) {X[index(j,t,T)] = val;}
  void setX(const std::vector<int>& data) {X = data;}
  void setI(int j, int t, int val) {I[index(j,t,T)] = val;}
  void setI(const std::vector<int>& data) {I = data;}

  //getters
  int getJ() {return J;};
  int getT() {return T;};
  int getX(int j, int t) {return X[index(j,t,T)];};
  container getX(){return X;};
  int getI(int j, int t) {return I[index(j,t,T)];};
  container getI(){return I;};

  int* toX(int j, int t) {return &X[index(j,t,T)];};
  int* toI(int j, int t) {return &I[index(j,t,T)];};

  const_iterator XBegin() {return X.begin();};
  const_iterator XEnd() {return X.end();};

  const_iterator IBegin() {return I.begin();};
  const_iterator IEnd() {return I.end();};

private:
  int J; //number of items
  int T; //number of periods
  container X; //production of item j in period t
  container I;  //inventory of item j at the end of period t
};


#endif // VARIABLES_H_INCLUDED
