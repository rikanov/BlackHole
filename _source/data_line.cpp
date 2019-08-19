#include "data_line.h"

int DataLine::_counter = 0;
int DataLine::_maxSize = 0;
DataLine ** DataLine::__cachedData = new DataLine *[5000];

DataLine::DataLine(const int& size)
    :_size(size)
    ,_index(_counter)
{
    if (_maxSize < size)
    {
        _maxSize = size;
    }
    __chains = new Chain [size];
    _pRest = _pLoad = __chains;
    __cachedData[_counter++] = this;
}

DataLine::DataLine(const Chain * C,const int & S)
    :DataLine(S)
{
    load(C, S);
    _pRest = _pLoad;
}

DataLine::DataLine(const Chain* C1,const int& S1,const Chain* C2,const int& S2)
    :DataLine(S1 + S2)
{
    load(C1,S1);
    _pRest = _pLoad;
    load(C2,S2);
}

DataLine::DataLine(const Chain* C1, const int& S1, const Chain* C2, const int& S2,const Chain* C3,const int& S3)
    :DataLine(S1 + S2 + S3)
{
    load(C1,S1);
    _pRest = _pLoad;
    load(C2,S2);
    load(C3,S3);
}

void DataLine::load(const Chain* C,const int& S)
{
    for (int id = 0; id < S; ++id)
        *(_pLoad++) = *(C++);
}

const DataLine * DataLine::getDataLine(const unsigned char& token) const
{
    const DataLine * ret = nullptr;
    const Chain * c = __chains;
    for (int id = 0; id < _size; ++id)
    {
        if (c->getStep() == token)
        {
            ret = c->getData();
            break;
        }
        ++c;
    }
    return ret;
}

const Chain * DataLine::get(const int& index) const
{
  return __chains + index;
}
const Chain* DataLine::getRandom() const
{
    srand(time(NULL));
    const int rndIndex = rand() % restIndex();
    return __chains + rndIndex;
}

const unsigned char DataLine::getRandomStepID() const
{
    return getRandom()->getStep();
}

const unsigned int DataLine::nth(const int& index) const
{
    return int(__chains[index].getStep());
}

bool DataLine::writeToFile(const std::string& file_name)
{
  std::ofstream out(file_name);
  out << std::hex << counter() + 1 << std::endl;
  for (int id = 0; id < counter(); ++id)
  {
    try {
      out << (*__cachedData[id]);
      out << std::endl;
    }
    catch (...)
    {
      return false;
    }
  }
  out.close();
  return true;
}

const DataLine * DataLine::readFromFile(const std::string& file_name)
{
  std::ifstream in(file_name);
  int size;
  in >> std::hex >> size;
  delete[] __cachedData;
  __cachedData = new DataLine *[size];
  DataLine ** next = __cachedData + 1; _counter = 1;
  std::string nextLine;
  getline(in,nextLine);
  while (getline(in,nextLine))
  {
    int size;
    std::istringstream splittedLine(nextLine);
    splittedLine >> std::hex >> size;
    *next = new DataLine(size);
    (**next) << splittedLine;
    if(_counter < 120)
    {
        std::cout <<  *next  << std::endl;
    }
  }
  return *next;
}

DataLine::~DataLine()
{
    for (int id = 0; id < _size; ++id)
    {
        delete __chains[id].getData();
    }
    --_counter;
    delete[] __chains;
}

// ---- outer functions / operators ---- //

std::ostream& operator<<(std::ostream& out,const DataLine& DL)
{
  if (DL.size() < 0x10)
    out << 0;
  out << std::hex << DL.size() << " ";
  for (int id = 0; id < DL.size(); ++id)
  {
    if (id == DL.restIndex())
    {
      out << "FF 000 ";
    }
    const DataLine * pDL = DL.get(id)->getData();

    if (DL.nth(id) < 0x10)
      out << 0;
    out << (DL.nth(id)) << ' ';

    const int index = pDL ? pDL->getIndex() + 1 : 0;
    if (index < 0x100)
      out << 0;
    if (index < 0x10)
      out << 0;
    
    out << index << ' ';
  }
  return out << std::dec;
}

void operator<<(DataLine& DL, std::istringstream& is)
{
  int next;
  int shiftingRest = 1;
  while (is >> std::hex >> next)
  {
    int address;
    is >> address; // address can be dummy in order to keep the source file readable 

    if (next != 0xFF)
    {
      *(DL._pLoad++) = Chain(next,address == 0 ? nullptr : DataLine::__cachedData[address]);
      DL._pRest += shiftingRest;
    }
    else
    {
      shiftingRest = 0;
    }
  }
  if (DL.getIndex() < 20)
  {
    std::cout << DL << std::endl;
  }
}
