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

#ifndef SSTACK__H
#define SSTACK__H

#include "str_step.h"

class StepStack
{
  const int _stackSize;
  // Store steps for UI (undo, redo)
  Step * __moveHistory,*_currentMove,*_lastMove;

public:
  StepStack(const int& S = MAX_NUMBER_OF_MOVES);
  virtual ~StepStack();
  bool isStarted() const {
    return _currentMove != __moveHistory + 1;
  }
  bool isTheLastMove() const {
    return _currentMove == _lastMove;
  }
  int stepCount() const {
    return (_currentMove - __moveHistory);
  }
  const Step& moveHistory(const int& index) const {
    return index < 0 ? *(_currentMove + index + 1) : __moveHistory[index];
  }
  void resetStack();
  void storeStep(Step S);
  void undoStep();
  void redoStep();
};

#endif
