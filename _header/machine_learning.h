/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2019  Robert Ikanov, robert.ikanov@gmail.com
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef MACHINELEARNING_H
#define MACHINELEARNING_H

#include "engine.h"
#include "data_line.h"

/**
 * @todo write docs
 */

class MachineLearning :  public Engine
{
  int _metaForsight;
  int _metaDepth;
  
  StepStack  __learningHistory;

public:
  MachineLearning(const int& meta_depth = MAX_DEPTH_OF_CACHE, const int& deep_search = DEPTH_TO_BUILD_CACHE);
    ~MachineLearning();
    DataLine * meta(Turn T);
    DataLine * meta(Turn T /*in*/, Result& /*out*/);
   // virtual void getUsableSteps() override;
};

#endif // MACHINELEARNING_H
