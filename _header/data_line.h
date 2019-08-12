#include "chain.h"

#ifndef DATA_LINE_HEADER
#define DATA_LINE_HEADER

class DataLine
{
  static int _counter;
  static int _maxSize;
  const int _index;
  const int _size;
  Chain * _pLoad;
  Chain * _pRest;
  Chain * __chains;

  void load(const Chain*,const int&);

public:
  DataLine(const int&);
  DataLine(const Chain*,const int&);
  DataLine(const Chain*,const int&,const Chain*,const int&);
  DataLine(const Chain*,const int&,const Chain*,const int&,const Chain*,const int&);
  ~DataLine();

  const unsigned int nth(const int&) const;
  const DataLine* get(const unsigned char&) const;
  const Chain* getRandom() const;
  const unsigned char getRandomStepID() const;
  const int& getIndex() const { return _index; }
  const int& size() const { return _size; }
  const int restIndex() const { return _pRest - __chains; }
  friend std::ostream& operator << (std::ostream&, const DataLine&);

  static const int& counter() { return _counter; }
  static const int& maxSize() { return _maxSize; }
};

#endif
