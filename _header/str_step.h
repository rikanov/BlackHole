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
 
#ifndef STR_STEP_H
#define STR_STEP_H

#include "str_node.h"
#include "step_mapping.h"
#include <iostream>

class Step
{
    static const StepMapping * _mapper;
  mutable char _name[3] = {};
  unsigned char _token = 0xFF;
  short int _mappingValue = 0;
  Node ** _stone;
  Node * _place;

public:
  Step() : _stone(nullptr),_place(nullptr) {}
  Step(Node ** s,Node * p) : _stone(s),_place(p) {}
  Step(const Step&) = default;
  bool isValid() const;
  void revertableStep();

  Node * place() const;
  bool operator == (const Step& S) const;
  bool operator != (const Step& S) const;
  bool notInv (const Step& S) const; // are they not inverted steps of each other ?
  bool inv (const Step& S) const; // are they inverted steps of each other ?
  
  const char* whatIs() const;
  void setToken(const unsigned char& t) { _token = t; }
  const unsigned char& getToken() const { return _token; }
  void printData() const { printf("%s->(%d, %d) ",whatIs(),_place->row,_place->col);}

  static bool createStep(Node **,const int&,Step&);
  static const unsigned char flip[];
};
#endif
