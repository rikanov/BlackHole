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
 
#include "engine.h"

Engine::Engine(const int& S,const int& L)
  :Game(S)
  ,_bound(L)
  ,_level(0)
{
}

Engine::~Engine()
{
}

Engine::Result Engine::seek0(Engine::Turn T,const bool& fast_check)
{
  Step test;
  Node ** setOfStones = (T == YOUR_TURN) ? __collectionOfPlayer : __collectionOfProgram;
  if (fast_check)
  {
    for (Node** nextStone = setOfStones; *nextStone; ++nextStone)
    {
      for (int direction = 0; direction < 8; ++direction)
      {
        if (makeStep(nextStone,direction,test) && isWinnerStep(test))
        {
          return WON;
        }
      }
    }
  }
  else
  {
    for (Node** nextStone = setOfStones; *nextStone; ++nextStone)
    {
      for (int direction = 0; direction < 8; ++direction)
      {
        if (makeStep(nextStone,direction,test))
        {
          return isWinnerStep(test) ? WON : UNSURE;
        }
      }
    }
  }
  return UNSURE;
}

Engine::Result Engine::seek(Turn T,const int& depth,const bool& fast_check,const Step& exclusion,const Step& next_exclusion)
{
  if (depth == 0)
  {
    return seek0(T,fast_check);
  }
  bool fail = true;
  Step test;
  Node ** setOfStones = (T == YOUR_TURN) ? __collectionOfPlayer : __collectionOfProgram;
  Turn nextTurn = (T == YOUR_TURN) ? MY_TURN : YOUR_TURN;
  for (Node** nextStone = setOfStones; *nextStone; ++nextStone)
  {
    for (int direction = 0; direction < 8; ++direction)
    {
      if (makeStep(nextStone,direction,test) && (test || exclusion))
      {
        if (isWinnerStep(test))
        {
          return WON;
        }
        if (depth == 0)
        {
          continue;
        }
        test.revertableStep();
        const Result tip = seek(nextTurn,depth - 1,!fail,test,next_exclusion);
        test.revertableStep();
        switch (tip)
        {
        case UNSURE:
          if (fast_check)
          {
            return UNSURE;
          }
          fail = false;
          break;
        case LOST:
          return WON;
        case WON:
          break;
        default:
          break;
        };
      }
    }
  }
  return fail ? LOST : UNSURE;
}

int Engine::getAllowedSteps(const bool& shuffle)
{
  int count = 0;
  Step next;
  for (Node** nextStone = _getStepsForAi ? __collectionOfProgram : __collectionOfPlayer; *nextStone; ++nextStone)
  {
    for (int direction = 0; direction < 8; ++direction)
    {
      if (makeStep(nextStone,direction,next))
      {
        __allowedSteps[count++] = next;
      }
    }
  }
  if (shuffle)
    for (int shuffles = count; shuffles; )
    {
      const int i1 = rand() % count;
      const int i2 = rand() % count;
      if (i1 != i2)
      {
        std::swap(__allowedSteps[i1],__allowedSteps[i2]);
      }
      else
      {
        --shuffles;
      }
    }
  return count;
}

void Engine::getUsableSteps()
{
  bool fastCheck = false;
  _numberOfUsableSteps = 0;
  for (int id = getAllowedSteps(); id > 0; --id)
  {
    Step test = __allowedSteps[id - 1];
    if (isWinnerStep(test))
    {
      _numberOfUsableSteps = 1;
      __usableSteps[0] = test;
      return;
    }
    if (_level == 0)
    {
      __usableSteps[_numberOfUsableSteps++] = test;
      continue;
    }
    test.revertableStep();
    const Result tip = seek(_getStepsForAi ? YOUR_TURN : MY_TURN,_level - 1,fastCheck);
    test.revertableStep();
    switch (tip)
    {
    case UNSURE:
      if (!fastCheck)
      {
        __usableSteps[_numberOfUsableSteps++] = test;
        fastCheck = (_numberOfUsableSteps > 2);
      }
      break;
    case LOST:
      _numberOfUsableSteps = 1;
      __usableSteps[0] = test;
      return;
    case WON:
      break;
    default:
      break;
    }
  }
}

Step Engine::getStep()
{
  Step bestFound;
  Step rescueSteps[MAX_NUMBER_OF_STONES * 8];
  int numberOfRescuedSteps = 0;
  for (_level = 0; _level <= _bound; _level += 1)
  {
    getUsableSteps();
    if (_numberOfUsableSteps == 1)
    {
      bestFound = __usableSteps[0];
      break; // don't think too much, an obviuos step is coming. Either winner or survivor
    }
    if (_numberOfUsableSteps == 0)
    {
      bestFound = rescueSteps[rand() % numberOfRescuedSteps];
      break; // we lost. try to rescue the game
    }
    // continue the searching and store the last known 'non-loser' steps for rescueing
    for (numberOfRescuedSteps = 0; numberOfRescuedSteps < _numberOfUsableSteps; ++numberOfRescuedSteps)
    {
      rescueSteps[numberOfRescuedSteps] = __usableSteps[numberOfRescuedSteps];
    }
  }
  if (_level > _bound /*obvious step not found*/)
  {
    do
    {
      bestFound = __usableSteps[rand() % _numberOfUsableSteps];
    } while (bestFound == moveHistory(-2) /*Do not step back! */);
  }
  return bestFound;
}
