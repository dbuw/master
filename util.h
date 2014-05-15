#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED

namespace BRKGA
{

//comparator for std::sort
template<class T1, class T2, class T = int, class Pred = std::less<T>>
struct sortPairSecond{
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        return p(left.second, right.second);
    }
};
typedef sortPairSecond<int,int> sortFitLess;
typedef sortPairSecond<int,int,int,std::greater<int>> sortFitGreater;

//return sorted indexes
template <typename T>
std::vector<size_t> sortIndexes(const std::vector<T> &v) {

 // initialize original index locations
   std::vector<size_t> index(v.size());
  for (size_t i = 0; i != index.size(); ++i){
      index[i] = i;
  }

  // sort indexes based on comparing values in v
  std::sort(index.begin(), index.end(),
       [&v](size_t i1, size_t i2) {return v[i1] < v[i2];});

  return index;
}

}
#endif // UTIL_H_INCLUDED
