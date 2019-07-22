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

 
#include "sstack.h"

StepStack::StepStack(const int& size)
  :_stackSize(size)
  ,__moveHistory(nullptr)
{
}

void StepStack::resetStack()
{
  // --- set step stacks for UI -- //
  delete[] __moveHistory; // purify it
  __moveHistory = new Step[_stackSize + 1];
  _currentMove = _lastMove = __moveHistory + 1;
  // -------------- //
}

void StepStack::storeStep(Step S)
{
  S.revertableStep();
  *(++_currentMove) = S;
  _lastMove = _currentMove;
}

void StepStack::undoStep()
{
  if (isStarted())
  {
    (_currentMove--)->revertableStep();
  }
}

void StepStack::redoStep()
{
  if ((_currentMove != _lastMove))
  {
    (++_currentMove)->revertableStep();
  }
}

StepStack::~StepStack()
{
  delete[] __moveHistory;
}
