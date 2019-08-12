#include "step_mapping.h"
#include "global.h"

int Pos::rowMax = 0;
int Pos::colMax = 0;

StepMapping::StepMapping(const int& size)
  :_numberOfCols(size)
  ,_numberOfRows(size + 2)
{
  Pos::rowMax = _numberOfRows;
  Pos::colMax = _numberOfCols;

  const int c = _numberOfRows * _numberOfCols;
  _mappingTable = new short int * [c];
  for (int id = 0; id < c; ++id)
  {
    _mappingTable[id] = new short int[c]();
  }
  Pos dir[] = { { 1,-1 }, {1, 0}, {1, 1}, {0, 1} };
  int stepVal = 0;
  for (int index = 0; index < c; ++index)
  {
    Pos start(index / _numberOfCols, index % _numberOfCols);
    for (int direction = 0; direction < 4; ++direction)
    {
      for (Pos end = start + dir[direction]; end.valid(); end += dir[direction])
      {
        const int t1 = start.index();
        const int t2 = end.index();
        _mappingTable[t1][t2] = ++stepVal;
        _mappingTable[t2][t1] = -stepVal;
      }
    }
  }
}

StepMapping::~StepMapping()
{
  for (int id = 0; id < _numberOfCols * _numberOfCols; ++id)
  {
    delete[] _mappingTable[id];
  }
  delete[] _mappingTable;
}

const short int& StepMapping::getStepValue(const int& r1,const int& c1, const int& r2,const int& c2) const
{
  //  std::cout << r1 << ',' << c1 << " : " << r2 << ',' << c2 << std::endl;
  //  std::cout << _mappingTable [ (r1 - 1) * _numberOfCols + c1 - 1 ] [ (r2 - 1) * _numberOfCols + c2 - 1 ] << std::endl;
  return _mappingTable [ (r1 - 1) * _numberOfCols + c1 - 1 ] [ (r2 - 1) * _numberOfCols + c2 - 1 ];
}

const short int& StepMapping::getStepValue(const int& B,const int& C) const
{
  return _mappingTable[B][C];
}
