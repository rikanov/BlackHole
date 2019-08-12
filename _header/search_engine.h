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

#ifndef SEARCH_ENGINE_HEADER__H
#define SEARCH_ENGINE_HEADER__H

#include "thread_engine.h"

class SearchEngine : public CoreEngine
{
  ThreadEngine * __threads;
public:
  SearchEngine(const int& S,const int& L)
    :CoreEngine(S,L) 
  {
  }
  virtual ~SearchEngine()
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
  int getAllowedSteps(const bool& shuffles = true);
  void getUsableSteps();
  Step getStep();
};

#endif

