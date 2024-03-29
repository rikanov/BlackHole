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


#include "basicui.h"
 //#include <unistd.h>

static const int AUTOPLAY_LEVEL1 = 7;
static const int AUTOPLAY_LEVEL2 = 6;

BasicUI::BasicUI(const int& size,const int& level,const bool& player_begin,const bool& auto_play)
  :_autoPlay(auto_play)
{
  _engine = new Engine(5, 11);
  //_engine->setRoot(DataLine::readFromFile("teszt.txt", false));
   _engine->mergeFiles();
  _engine->getStepsForAi(true);
  _engine->invertedSearch(player_begin);
  _engine->boundLevel(level);
  _isPlayerTurn = player_begin;
}

BasicUI::~BasicUI()
{
  delete _engine;
}

void BasicUI::start()
{
  CLR();
  _engine->show();
  for (bool finish = false; !finish;)
  {
    if (_isPlayerTurn)
    {
      finish = _autoPlay ? autoPlay(AUTOPLAY_LEVEL1) : yourTurn();
      _isPlayerTurn = false;
    }
    else
    {
      finish = _autoPlay ? autoPlay(AUTOPLAY_LEVEL2) : myTurn();
      _isPlayerTurn = true;
    }
  }
}

bool BasicUI::myTurn()
{
  bool win = false;
  Step st = _engine->getStep();
  _engine->storeStep(st);
  CLR();
  _engine->show();
  if (_engine->isWinnerStep(st))
  {
    std::cout << "AI WON !!!" << std::endl;
    win = true;
  }
  return win;
}

bool BasicUI::yourTurn()
{
  bool win = false;
  Step st;
  for (bool valid = false; !valid;)
  {
    std::cout << std::endl << "> " << std::flush;
    std::cin.clear();
    std::cin.ignore(8,'\n');
    int id,dir;
    std::cin >> id >> dir;
    if (id == 0 && dir < 0 && _engine->isStarted())
    {
      _engine->undoStep();
      CLR();
      _engine->show();
      Sleep(1);
      _engine->undoStep();
      CLR();
      _engine->show();
      continue;
    }
    else if (id == 0 && dir > 0)
    {
      _engine->redoStep();
      CLR();
      _engine->show();
      Sleep(1);
      _engine->redoStep();
      CLR();
      _engine->show();
      continue;
    }
    else
    {
      valid = _engine->makeStep(id,dir,st);
    }

    if (!valid)
    {
      std::cout << "ERR: " << id << ':' << dir << std::endl;
    }
    else
    {
      st.setToken(dir + (abs(id) - 1) * 8);
    }
  }
  _engine->storeStep(st);
  CLR();
  _engine->show();
  if (_engine->isWinnerStep(st))
  {
    std::cout << "YOU WON !!!" << std::endl;
    win = true;
  }
  return win;
}

bool BasicUI::autoPlay(const int& level)
{
  bool win = false;
  if (level > 0)
  {
    _engine->boundLevel(level);
  }
  Step st = _engine->getStep();
  _engine->storeStep(st);
  CLR();
  _engine->show();
  if (_engine->isWinnerStep(st))
  {
    std::cout << "THE" << (_isPlayerTurn ? " HEURISTIC " : " SIMPLIER") << " AI WON !!!" << std::endl;
    win = true;
  }
  _engine->swapOpponents();
  return win;
}


