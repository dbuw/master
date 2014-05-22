#ifndef FIXLINKS_H_INCLUDED
#define FIXLINKS_H_INCLUDED

class FixLinks{
public:
  FixLinks(Data* d, Variables* v, Sequence* s, Encoding* e)
  : data(d)
  , vars(v)
  , sequence(s)
  , enc(e)
  {}

  void run()
  {

  }
private:
  Data* data;
  Variables* vars;
  Sequence* sequence;
  Encoding* enc;
};

#endif // FIXLINKS_H_INCLUDED
