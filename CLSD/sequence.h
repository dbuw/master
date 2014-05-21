#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <vector>
#include <algorithm>
class Sequence {
public:

    struct Operation {
    Operation(){}
    Operation(int j_, int t_, int* X_)
      : j(j_)
      , t(t_)
      , X(X_)
    {}
    int j;
    int t;
    int* X;

    int pSequence;
    int pSetup;
  };

public:

  typedef std::vector<Operation>::iterator iterator;
  Sequence(){}

  void push_back(const Operation& o) {
    seq.push_back(o);
  }

  void push_back(int j, int t, int* X) {
    Operation o(j,t,X);
    seq.push_back(o);
  }

  iterator begin() {return seq.begin();}
  iterator end() {return seq.end();}
  iterator begin(int t) {
    auto it = seq.begin();
    while(it->t != t) {
      if (it == seq.end()){return seq.end();}
      ++it;
    }
    return it;
  }
  iterator end(int t) {
    auto it = begin(t);
    while(it->t == t) {
      if (it == seq.end()){return seq.end();}
      ++it;
    }
    return it;
  }

  void insertOrdered(Operation j, int t)
  {
//    auto first = begin(t);
//    auto last = end(t);
//
//    while (first != last){
//      if (j.pSequence < first->pSequence){
//          insert(first, j);
//      }
//      ++first;
//    }
//
//    if (first == last){
//      insert(first, j);
//    }
    auto first = seq.begin();
    auto last = end(t);
    while (j.t < t){
      ++first;
    }
    if (first->t == t){
      while (first != last){
        if (j.pSequence < first->pSequence){
            insert(first, j);
        }
        ++first;
      }
    }
    insert(first, j);
  }
  //returns an iterator to a previous setup of j
  iterator prevSetup(iterator curr) {
    auto it = curr;
    if(curr != seq.begin()) {
      --it;
      //go backwards in sequence
      while(curr->j != it->j) {
        //if no previous setup, return current setup
        if(it == seq.begin()) {
          return curr;
        }
        --it;
      }
    }
    return it;
  }
  //returns an iterator to the next setup of j
  iterator nextSetup(iterator curr) {
    auto it = curr;
    if(curr != seq.end()) {
      ++it;
      //go backwards in sequence
      while(curr->j != it->j) {
        //if no previous setup, return current setup
        if(it == seq.end()) {
          return curr;
        }
        ++it;
      }
    }
    return it;
  }

  void reverse() {std::reverse(seq.begin(),seq.end());}

  iterator erase(iterator it) {return seq.erase(it);}
  bool empty(){return seq.empty();}

  iterator insert(iterator pos, const Operation& o){
    return seq.insert(pos, o);
  }

private:
  std::vector<Operation> seq;
};



#endif // SEQUENCE_H
