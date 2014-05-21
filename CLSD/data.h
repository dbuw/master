#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

#include "../util/util.h"
class Data {
public:
  typedef std::vector<int> container;
  typedef container::const_iterator const_iterator;

  Data() {}

  //setters
  void setJ(int i) {J = i;};
  void setT(int i) {T = i;};
  void setD(const container& i){d = i;};
  void setC(const container& i){C = i;};
  void setP(const container& i){p = i;};
  void setH(const container& i){h = i;};
  void setSC(const container& i){c = i;};
  void setST(const container& i){s = i;};

  //getters
  int getJ() {return J;};
  int getT() {return T;};
  int getD(int j, int t) {return d[index(j,t,T)];};
  int getC(int t) {return C[t];};
  int getP(int j) {return p[j];};
  int getH(int j) {return h[j];};
  int getSC(int i, int j) {return c[index(i,j,J)];};
  int getST(int i, int j) {return s[index(i,j,J)];};
  //getters
  container getD() {return d;};
  const_iterator dBegin() {return d.begin();};
  const_iterator dEnd() {return d.end();};
  container getC() {return C;};
  const_iterator CBegin() {return C.begin();};
  const_iterator CEnd() {return C.end();};
  container getP() {return p;};
  const_iterator pBegin() {return p.begin();};
  const_iterator pEnd() {return p.end();};
  container getH() {return h;};
  const_iterator hBegin() {return h.begin();};
  const_iterator hEnd() {return h.end();};
  container getSC() {return c;};
  const_iterator cBegin() {return c.begin();};
  const_iterator cEnd() {return c.end();};
  container getST() {return s;};
  const_iterator sBegin() {return s.begin();};
  const_iterator sEnd() {return s.end();};
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
