#ifndef ENCODING_H_INCLUDED
#define ENCODING_H_INCLUDED

#include "../util/util.h"

// Encoding is done in the following way
// A chromosome has the size T*J*2, with T*J genomes to indicate
// setup priorities (low means high priority) and T*J genomes to indicate
// sequence priorities (low means high priority).
// Each half is ordered by periods.

class Encoding {
public:

  typedef std::vector<int> container;
  typedef container::iterator iterator;

  Encoding(container v, int j, int t)
    : enc(v)
    , J(j)
    , T(t)
  {}
  Encoding(iterator first, iterator last, int j, int t)
    : enc(first,last)
    , J(j)
    , T(t)
  {}

  //get an ordered index array, indicating the order to sequence
  //items by their index in period t
  int sequencePriority(int j, int t){
    return enc[J*T+index(t,j,J)];
  }
  int setupPriority(int j, int t){
    return enc[index(t,j,J)];
  }

  std::vector<unsigned> sortedSequencePriorities(int t) {
    return getSortedIndex(1, t);
  }
  //get an ordered index array, indicating the order to setup
  //items by their index in period t
  std::vector<unsigned> sortedSetupPriorities(int t) {
    return getSortedIndex(0, t);
  }


private:
  std::vector<unsigned> getSortedIndex(bool half = 0, int t = 0) {
    iterator first;
    iterator last;

    if(half == 0) {
      first = enc.begin()+t*J;
    } else {
      first = enc.begin()+(T*J)+t*J;
    }
    last = first+J;

    std::vector<int> range(first, last);

    return sortIndexes(range);
  }

private:
  container enc;

  int J;
  int T;

};

#endif // ENCODING_H_INCLUDED
