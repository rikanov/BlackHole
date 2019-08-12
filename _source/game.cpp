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

#include "game.h"

Game::Game(const int& S)
  : Board(S)
{
  // --- Collections of stones --- /
  // allocate memory
  __collectionOfPlayer = new Node*[_cols + 1];     /*null-terminated array*/
  __collectionOfProgram = new Node*[_cols + 1];  /*null-terminated array*/
                           // default positions
  reset();
}

void Game::reset()
{
  for (int row = 1; row < _rows + 1; ++row)
  {
    for (int col = 1; col < _cols + 1; ++col)
    {
      __theGrid[row][col].occupied = 0;
    }
  }
  for (int id = 0; id < _cols; ++id)
  {
    __collectionOfPlayer[id] = &__theGrid[1][id + 1];
    __collectionOfPlayer[id]->occupied = -id - 1;
    __collectionOfProgram[id] = &__theGrid[_rows][id + 1];
    __collectionOfProgram[id]->occupied = id + 1;
  }
  // null-terminate arrays for the opponents' stones
  __collectionOfPlayer[_cols] = nullptr;
  __collectionOfProgram[_cols] = nullptr;

  // --- set step stacks for UI -- //
  resetStack();
}

bool Game::makeStep(const int& token,Step& step, const bool& flip) const
{
  const int a = flip ? Step::flip[abs(token)] : abs(token), s = token < 0 ? -1 : 1; // auxiliary
  const int stone = s * (1 + a / 8);
  const int dir = a % 8;
  const bool succes = makeStep( stone, dir, step);
  step.setToken(a);
  return succes;
}

bool Game::makeStep(const int& id,const int& dir,Step& step) const
{
  Node ** stone = nullptr;
  if (id < 0)
  {
    stone = __collectionOfPlayer - (id + 1);
  }
  else if (id > 0)
  {
    stone = __collectionOfProgram + id - 1;
  }
  return stone ? Step::createStep(stone,dir,step) : false;
}

Game::~Game()
{
}
