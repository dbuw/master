#ifndef SEQUENCEUTIL_H_INCLUDED
#define SEQUENCEUTIL_H_INCLUDED

#include "sequence.h"
#include "data.h"

typedef std::vector<Sequence::Operation>::iterator iterator;

int setupTimes(iterator first, iterator last, Data* data)
{
    int sum = 0;
    while(first != last){
        sum += data->getST(first->j, (first+1)->j);
    ++first;
    }
    return sum;
}

int setupCost(iterator first, iterator last, Data* data)
{
    int sum = 0;
    while(first != last){
        sum += data->getSC(first->j, (first+1)->j);
        ++first;
    }
    return sum;
}

int productionTimes(iterator first, iterator last, Data* data)
{
    int sum = 0;
    while(first != last){
        sum += *first->X * data->getP(first->j);
        ++first;
    }
    return sum;
}

int consumption(iterator first, iterator last, Data* data)
{
    return productionTimes(first,last,data) + setupTimes(first,last,data);
}

#endif // SEQUENCEUTIL_H_INCLUDED

