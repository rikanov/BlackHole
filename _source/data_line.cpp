#include "data_line.h"

int DataLine::_counter = 0;
int DataLine::_maxSize = 0;
DataLine::DataLine(const int& size)
    :_size(size)
    ,_index(_counter)
{
    if (_maxSize < size)
    {
        _maxSize = size;
    }
    __chains = new Chain [size];
    _pLoad = __chains;
    ++_counter;
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

const DataLine * DataLine::get(const unsigned char& token) const
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

std::ostream& operator<<(std::ostream& out, const DataLine& DL)
{
    out << ' ' << DL.size() << ": ";
    for (int id = 0; id < DL.size(); ++id)
    {
        if (id == DL.restIndex())
        {
            out << " | ";
        }
        out << int(DL.nth(id)) << ' ';
    }
    return out;
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
