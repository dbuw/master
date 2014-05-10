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

}
#endif // UTIL_H_INCLUDED
