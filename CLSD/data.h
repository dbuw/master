#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

class Data
{
public:
  typedef std::vector<int> container;
  typedef container::const_iterator const_iterator;

  Data();

  //setters
  void setNumberOfItems(int v){J = v;};
  void setNumberOfPeriods(int v){T = v;};

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
  int getD(int j, int t){return d[indexJT(j,t)];};
  int getC(int t){return C[t];};
  int getP(int j){return p[j];};
  int getH(int j){return h[j];};
  int getSC(int i, int j){return c[indexIJ(i,j)];};
  int getST(int i, int j){return s[indexIJ(i,j)];};
  //getters
  container dGet(){return d;};
  const_iterator dBegin(){return d.begin();};
  const_iterator dEnd(){return d.end();};
  container CGet(){return C;};
  const_iterator CBegin(){return C.begin();};
  const_iterator CEnd(){return C.end();};
  container pGet(){return p;};
  const_iterator pBegin(){return p.begin();};
  const_iterator pEnd(){return p.end();};
  container hGet(){return h;};
  const_iterator hBegin(){return h.begin();};
  const_iterator hEnd(){return h.end();};
  container cGet(){return c;};
  const_iterator cBegin(){return c.begin();};
  const_iterator cEnd(){return c.end();};
  container sGet(){return s;};
  const_iterator sBegin(){return s.begin();};
  const_iterator sEnd(){return s.end();};
private:
  int J; //number of items
  int T; //number of periods
  container d; //demand for item j in period t
  container C; //capacity in period t
  container p; //processing times
  container h; //holding costs
  container c; //sequence dependent setup costs
  container s; //sequence dependent setup times
};

#endif // DATA_H_INCLUDED
