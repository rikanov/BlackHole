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
 */
#ifndef STR_STEP_H
#define STR_STEP_H

#include "str_node.h"
#include <iostream>

struct Step
{
  Node ** stone;
  Node * place;

public:
  Step() : stone(nullptr),place(nullptr) {}
  Step(Node ** s,Node * p) : stone(s),place(p) {}
  Step(const Step&) = default;
  bool isValid() const {
    return stone != nullptr && place != nullptr;
  }
  void revertableStep()
  {
    place->occupied = (*stone)->occupied; // put down
    (*stone)->occupied = 0;              // and pick up
    std::swap(*stone,place);
  }

  bool operator == (const Step& S) const
  {
    return isValid() && S.isValid() && *stone == *S.stone && *place == *S.place;
  }

  bool operator != (const Step& S) const
  {
    return !isValid() || !S.isValid() || *stone != *S.stone || *place != *S.place;
  }
  bool operator || (const Step& S) const // are they not inverted steps to each other ?
  {
    return !isValid() || !S.isValid() || place != *S.stone || *stone != S.place;
  }
  bool operator && (const Step& S) const // are they inverted steps to each other ?
  {
    return isValid() && S.isValid() && *stone == S.place && place == *S.stone;
  }
  void printData() const
  {
    printf("X%d->(%d, %d) ",(*stone)->occupied,place->row,place->col);
  }
};

#endif
