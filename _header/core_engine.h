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

#ifndef CORE_ENGINE_HEADER__H
#define CORE_ENGINE_HEADER__H

#include "game.h"

class CoreEngine : public Game
{
protected:
  Step __usableSteps[MAX_NUMBER_OF_STONES * 8];
  Step __allowedSteps[MAX_NUMBER_OF_STONES * 8];

public:
  enum Result
  {
    LOST = -1,
    UNSURE = 0,
    WON = 1
  };
  enum Turn
  {
    MY_TURN,
    YOUR_TURN
  };
protected:
  int _bound;
  int _level;
  bool _getStepsForAi = true;
public:
  CoreEngine(const int& S,const int& L) 
    :Game(S)
    ,_bound(L)
    ,_level(0)
  {
  }
  virtual ~CoreEngine() 
  {
  }
  void swapOpponents() {
    std::swap(__collectionOfPlayer,__collectionOfProgram);
  }
  const int& boundLevel() const {
    return _bound;
  }
  void boundLevel(const int& bound) {
    _bound = bound;
  }
  void seekerSwap() {
    _getStepsForAi = !_getStepsForAi;
  }
  void getStepsForAi(const bool& t) {
    _getStepsForAi = t;
  }
  const bool& getStepsForAi() const {
    return _getStepsForAi;
  }
};

#endif