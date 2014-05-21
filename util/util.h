#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

#include <algorithm>
//comparator for std::sort
template<class T1, class T2, class T = int, class Pred = std::less<T>>
struct sortPairSecond {
  bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
    Pred p;
    return p(left.second, right.second);
  }
};
typedef sortPairSecond<int,int> sortFitLess;
typedef sortPairSecond<int,int,int,std::greater<int>> sortFitGreater;


//return sorted indexes
template <typename T>
std::vector<unsigned> sortIndexes(const std::vector<T> &v)
{

// initialize original index locations
  std::vector<unsigned> index(v.size());
  for(unsigned i = 0; i != index.size(); ++i) {
    index[i] = i;
  }

  // sort indexes based on comparing values in v
  std::sort(index.begin(), index.end(),
  [&v](unsigned i1, unsigned i2) {return v[i1] < v[i2];});

  return index;
}

//indexing for 2d data in 1d sequential container
unsigned index(int row, int col, int Cols)
{
  return (Cols*row+col);
}


#endif // UTIL_H_INCLUDED
