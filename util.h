#ifndef UTIL_H_INCLUDED
#define UTIL_H_INCLUDED


//comparator for std::sort
template<class T1, class T2, class T = int, class Pred = std::less<T>>
struct sortPairFirst{
    bool operator()(const std::pair<T1,T2>&left, const std::pair<T1,T2>&right) {
        Pred p;
        return p(left.first, right.first);
    }
};
typedef sortPairFirst<int,int> sortFitLess;
typedef sortPairFirst<int,int,int,std::greater<int>> sortFitGreater;
#endif // UTIL_H_INCLUDED
