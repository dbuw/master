#ifndef VARIABLES_H_INCLUDED
#define VARIABLES_H_INCLUDED

class Variables
{
public:
  typedef std::vector<int> container;
  typedef container::const_iterator const_iterator;

  Variables(){}

  //setters
  void setNumberOfItems(int v){J = v;};
  void setNumberOfPeriods(int v){T = v;};
  void setX(int j, int t, int val){X[indexJT(j,t)] = val;};

  //indexes
  unsigned indexJT(int j, int t){
    return index(j,t,T);
  }
  unsigned indexIJ(int i, int j){
    return index(i,j,J);
  }
  unsigned index(int row, int col, int Cols){
    return (Cols*row+col);
  }
  //getters
  int getJ(){return J;};
  int getT(){return T;};
  int getX(int j, int t){return X[indexJT(j,t)];};
  int getI(int j, int t){return I[indexJT(j,t)];};
  //getters
  container xGet(){return X;};
  const_iterator dBegin(){return X.begin();};
  const_iterator dEnd(){return X.end();};
  container iGet(){return I;};
  const_iterator IBegin(){return I.begin();};
  const_iterator IEnd(){return I.end();};

private:
  int J; //number of items
  int T; //number of periods
  container X; //production of item j in period t
  container I;  //inventory of item j at the end of period t
};


#endif // VARIABLES_H_INCLUDED
