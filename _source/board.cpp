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


#include "board.h"

Board::Board(const int& S)
  :_rows(S + 2)
  ,_cols(S)
{
  // --- Create grid --- //
  // allocate size
  __theGrid = new Node*[_rows + 2];
  for (int row = 0; row < _rows + 2; ++row)
  {
    __theGrid[row] = new Node[_cols + 2];
  }
  // set borders -> vertical
  for (int id = 1; id < _cols + 2; ++id)
  {
    __theGrid[0][id].occupied = WALL;
    __theGrid[_rows][id].occupied = WALL;
  }
  // set borders -> horizontal
  for (int id = 1; id < _rows + 2; ++id)
  {
    __theGrid[id][_cols].occupied = WALL;
    __theGrid[id][0].occupied = WALL;
  }
  // set auxiliary parameters and make topology
  for (int row = 1; row < _rows + 1; ++row)
  {
    for (int col = 1; col < _cols + 1; ++col)
    {
      __theGrid[row][col].occupied = 0;
      __theGrid[row][col].row = row;
      __theGrid[row][col].col = col;
      Node & toSet = __theGrid[row][col];
      for (int dir = 0; dir < 8; ++dir)
      {
        const int ver = (dir == 7 || dir < 2) - (2 < dir && dir < 6);
        const int hor = (0 < dir && dir < 4) - (4 < dir);
        toSet.next[dir] = &__theGrid[row + ver][col + hor];
      }
    }
  }
  // set the middle field of the board as the place of victory
  _WINNER_SPOT = &__theGrid[(_rows + 1) / 2][(_cols + 1) / 2];
  // --------------- //
}

static inline void NL() {
  std::cout << std::endl << '|';
}

void Board::show() const
{
  const char* separator = "---- ";
  const char* empty = "    |";
  for (int row = _rows; row > 0; --row)
  {
    NL();
    for (int col = 1; col <= _cols; ++col)
    {
      std::cout << separator;
    }
    NL();
    for (int col = 1; col <= _cols; ++col)
    {
      const Node *field = &(__theGrid[row][col]);
      const int CH = field->occupied;
      if (field == _WINNER_SPOT && CH == 0)
      {
        std::cout << " () |";
        continue;
      }
      if (CH < 0)
      {
        std::cout << ' ' << 'A' << (-1 * CH) << " |";
      }
      else if (CH > 0)
      {
        std::cout << ' ' << 'X' << (CH) << " |";
      }
      else
      {
        std::cout << empty;
      }
    }
  }
  NL();
  for (int col = 1; col <= _cols; ++col)
  {
    std::cout << separator;
  }
  NL();
}

Board::~Board()
{
  delete[] __collectionOfPlayer;
  delete[] __collectionOfProgram;
}

