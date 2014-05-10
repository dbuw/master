#ifndef SEQUENCE_H_INCLUDED
#define SEQUENCE_H_INCLUDED

struct operation
{
  int j;
  int t;
  int X;
};

class Sequence
{
public:
  Sequence(){}

private:
  std::vector<operation> seq;
};


#endif // SEQUENCE_H_INCLUDED
