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

#ifndef BOARD_H
#define BOARD_H

#include "str_step.h"

class Board
{
  const Node* _WINNER_SPOT;
protected:
  // Board grid [rows+2][columns+2]
  Node ** __theGrid;
  const int _rows;
  const int _cols;

  // Stones os players [columns]
  Node ** __collectionOfPlayer;
  Node ** __collectionOfProgram;

public:
  Board(const int&);
  virtual ~Board();
  const Node * getStone(const int & ID) const {
    return ID > 0 ? __collectionOfProgram[ID - 1] : __collectionOfPlayer[-ID - 1];
  }
  bool isFinished() const {
    return _WINNER_SPOT->occupied != 0;
  }
  bool isWinnerStep(const Step& S) const {
    return S.place() == _WINNER_SPOT;
  }
  void show() const;
};

#endif // BOARD_H
