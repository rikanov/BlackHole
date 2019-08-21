#ifndef CHAIN_HEADER
#define CHAIN_HEADER

#include "global.h"

class DataLine;
class Chain
{
  unsigned char _step = 0;
  const DataLine * _next;
public:
  Chain() : _step(0),_next(nullptr) {}
  Chain(const unsigned char & S, const DataLine * DL) : _step(S),_next(DL) {}
  virtual ~Chain();

  void step(unsigned char& s) { _step = s; }
  const unsigned char getStep() const { return _step; }
  const DataLine * getData() const { return _next; }
  void setData(const DataLine * DL) { _next = DL; }
  bool operator == (const Chain & C) const { return _step == C._step && _next == C._next; }
  bool operator != (const Chain & C) const { return _step != C._step || _next != C._next; }
};

#endif
