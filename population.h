#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <algorithm>
#include <utility>
namespace BRKGA {

//template <class T>
class Population {
  typedef int type;
  typedef std::vector<type> container;
  typedef typename container::size_type size_type;
  typedef typename container::iterator iterator;
  typedef typename container::const_iterator const_iterator;
  typedef unsigned index_type;
  typedef float fitness_type;
  typedef std::vector<std::pair<index_type, fitness_type>>::iterator fitnessIterator;


public:
  Population() {}
  Population(size_type popSize, size_type chromosomeSize)
    : pop(popSize*chromosomeSize,0)
    , fit(popSize)
    , popSz(popSize)
    , chSz(chromosomeSize)

  {
    initIndex();
  }

  Population(size_type popSize, size_type chromosomeSize, const container& Pop)
    : pop(Pop)
    , fit(popSize)
    , popSz(popSize)
    , chSz(chromosomeSize)

  {
    initIndex();
  }
  Population(const Population& p)
    : pop(p.pop)
    , fit(p.fit)
    , popSz(p.popSz)
    , chSz(p.chSz) {

  }

  void initIndex() {
    for(unsigned i = 0; i < popSz; ++i) {
      fit[i].first = i;
      fit[i].second = 0;
    }
  }

  size_type size() {return pop.size();};
  size_type chromosomeSize() {return chSz;};
  size_type populationSize() {return popSz;};
  iterator begin() {return pop.begin();};
  iterator end() {return pop.end();};
  const_iterator begin() const {return pop.begin();};
  const_iterator end() const {return pop.end();};

  iterator chromosomeBegin(size_type i) {
    if(i > popSz) {
      return pop.begin();
    }
    return (pop.begin()+(fit[i].first*chSz));
  };

  iterator chromosomeEnd(size_type i) {
    if(i > popSz) {
      return pop.end();
    }
    return pop.begin()+(fit[i].first*chSz+chSz);
  };

  fitnessIterator beginFitness() {
    return fit.begin();
  }

  fitnessIterator endFitness() {
    return fit.end();
  }

private:
  container pop; //datastructure for population
  std::vector<std::pair<index_type,fitness_type>> fit;
  size_type popSz; //size of population
  size_type chSz; //number of genes in a chromosome
};

}



#endif // POPULATION_H
