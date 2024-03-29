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

#ifndef STRUCT_NODE_H
#define STRUCT_NODE_H

#include "global.h"

struct Node
{
  Node* next[8] = {};
  int occupied = WALL;
  int row = 0,col = 0;
  bool operator == (const Node& N) const {
    return row == N.row && col == N.col;
  }
  bool operator != (const Node& N) const {
    return row != N.row || col != N.col;
  }
};

#endif
