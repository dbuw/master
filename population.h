#ifndef POPULATION_H
#define POPULATION_H

#include <vector>
#include <algorithm>
#include <utility>

template <class T>
class Population
{
    typedef T type;
    typedef std::vector<type> container;
    typedef typename container::size_type size_type;
    typedef typename container::iterator iterator;
    typedef typename container::const_iterator const_iterator;
    typedef unsigned index_type;
    typedef float fitness_type;
    typedef std::vector<std::pair<index_type, fitness_type>>::iterator fitnessIterator;


    public:
    Population(){}
    Population(size_type popSize, size_type chromosomeSize)
    : popSz(popSize)
    , chSz(chromosomeSize)
    {
    }

    Population(size_type popSize, size_type chromosomeSize, const container& Pop)
    : popSz(popSize)
    , chSz(chromosomeSize)
    , pop(Pop)
    {

    }
    Population(const Population<T>& p)
    : popSz(p.popSz)
    , chSz(p.chSz)
    , pop(p.pop)
    {

    }

    iterator begin(){return pop.begin();};
    iterator end(){return pop.end();};
    const_iterator begin() const {return pop.begin();};
    const_iterator end() const {return pop.end();};

    iterator chromosomeBegin(size_type i){
        if (i > popSz){
            return pop.begin();
        }
        return pop.begin()+(fit[i].second*chSz);
    };

    iterator chromosomeEnd(size_type i){
        if (i > popSz){
            return pop.end();
        }
        return pop.end()+(fit[i].second*chSz);
    };

    fitnessIterator beginFitness(){
        return fit.begin();
    }

    fitnessIterator endFitness(){
        return fit.end();
    }



    private:
    container pop; //datastructure for population
    std::vector<std::pair<index_type,fitness_type>> fit;
    size_type popSz; //size of population
    size_type chSz; //number of genes in a chromosome
};





#endif // POPULATION_H
