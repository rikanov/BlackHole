/*
* BlackHole -- a simple abstract board game designed by myself
* Copyright (C) 2019  Robert Ikanov, robert.ikanov@gmail.com
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
*/
#ifndef STEP_MAPPING
#define STEP_MAPPING


struct Pos
{
  static int rowMax;
  static int colMax;
  int row;
  int col;
  Pos() : row(0),col(0) {}
  Pos(int r,int c) : row(r),col(c) {}
  Pos operator+(const Pos & P) const
  {
    return Pos(row + P.row,col + P.col);
  }
  Pos & operator += (const Pos & P)
  {
    row += P.row;
    col += P.col;
    return *this;
  }
  bool valid() const
  {
    return 0 <= row && 0 <= col && row < rowMax && col < colMax;
  }
  int index() const
  {
    return row * colMax + col;
  }
};

class StepMapping
{
  short int ** _mappingTable;
  const unsigned short int _numberOfRows;
  const unsigned short int _numberOfCols;

public:
  StepMapping(const int&);
  ~StepMapping();

  const short int& getStepValue(const int&,const int&, const int&, const int&) const;
  const short int& getStepValue(const int&,const int&) const;
};
#endif 