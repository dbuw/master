#ifndef DATA_H_INCLUDED
#define DATA_H_INCLUDED

class data
{
public:
  typedef std::vector<int> container;
  typedef container::const_iterator const_iterator;

  data();

  //setters
  void setNumberOfItems(int v){J = v;};
  void setNumberOfPeriods(int v){T = v;};



  //getters
  int getJ(){return J;};
  int getT(){return T;};
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
