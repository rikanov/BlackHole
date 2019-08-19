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

#ifndef GAME_HEADER__H
#define GAME_HEADER__H

#include "board.h"
#include "cache.h"

class Game : public Board,
             public Cache
{
protected:

  int _numberOfUsableSteps;
  Step __usableSteps[MAX_NUMBER_OF_STONES * 8];
  Step __allowedSteps[MAX_NUMBER_OF_STONES * 8];

public:
  Game(const int& S);
  virtual ~Game();
  void reset();
  bool makeStep(const int&, Step& /*out*/, const bool& flip = false) const;
  bool makeStep(const int& id,const int&,Step& /*out*/) const;
};
#endif // !GAME_HEADER__H

