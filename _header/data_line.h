#ifndef DATA_LINE_HEADER
#define DATA_LINE_HEADER

#include "chain.h"
#include <fstream> 

class DataLine
{
  static int _counter;
  static int _maxSize;
  static DataLine ** __cachedData;

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
  const DataLine* getDataLine(const unsigned char&) const;
  const Chain * get(const int&) const;
  const Chain* getRandom() const;
  const unsigned char getRandomStepID() const;
  const int& getIndex() const { return _index; }
  const int& size() const { return _size; }
  const int restIndex() const { return _pRest - __chains; }
  void fillUp(std::istringstream&, bool);
  void swapBranches(const Chain *,const int&);
  static const int& counter() { return _counter; }
  static const int& maxSize() { return _maxSize; }
  static bool writeToFile(const std::string&);
  static const DataLine * readFromFile(const std::string&, bool);
  friend std::ostream& operator << (std::ostream&,const DataLine&);
  friend void operator << (DataLine &, std::istringstream&);
};

#endif
