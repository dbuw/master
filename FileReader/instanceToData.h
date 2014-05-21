#ifndef INSTANCETODATA_H_INCLUDED
#define INSTANCETODATA_H_INCLUDED

#include "instance.h"
#include "../CLSD/data.h"

class InstanceToData
{
public:
  InstanceToData()

  {}

  void convert(Instance* i, Data* d)
  {
    d->setJ(i->numberOfItems);
    d->setT(i->numberOfPeriods);
    d->setD(matrixToVector(i->demand));
    d->setH(unsignedToSignedVector(i->holdingCost));
    d->setP(unsignedToSignedVector(i->requiredCapacity));
    d->setC(unsignedToSignedVector(i->capacity));
    d->setSC(matrixToVector(i->setupCost));

    std::vector<int> v(i->numberOfItems*i->numberOfItems, 0);
    d->setST(v);

  }

  std::vector<int> unsignedToSignedVector(const std::vector<unsigned>& u){
    std::vector<int> s;
    for (auto i : u){
      s.push_back((int)i);
    }
    return s;
  }

  std::vector<int> matrixToVector(const std::vector<std::vector<unsigned>>& m){
    std::vector<int> v;
    for (auto i : m){
      for (auto j : i){
        v.push_back((int)j);
      }
    }
    return v;
  }
private:

};

#endif // INSTANCETODATA_H_INCLUDED
