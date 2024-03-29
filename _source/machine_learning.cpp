/*
 * <one line to give the program's name and a brief idea of what it does.>
 * Copyright (C) 2019  <copyright holder> <email>
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

#include "machine_learning.h"

MachineLearning::MachineLearning(const int& meta_depth, const int& deep_search)
    :Engine(5, 10)
    ,_metaDepth(meta_depth)
    ,_metaForsight(deep_search)
{
    __learningHistory.resetStack();
}

MachineLearning::~MachineLearning()
{
}

DataLine * MachineLearning::meta(Turn T)
{
    getAllowedSteps(false);
    int c; log("index ? ")
    std::cin >> c;
    storeStep(__allowedSteps[c]);
    char fn[5] = {};
    fn[0] = ('0' + c);
    fn[1] = '.';
    fn[2] = 'a';
    fn[3] = 'i';
    log2("file name:",fn)
    show();
    Result dummy;
    DataLine * root = meta(T,dummy);
    log2("counted:",DataLine::counter());
    log2("result:", dummy == UNSURE ? "unsure" : (dummy == WON ? "you lost" : "we won"))
    DataLine::writeToFile(fn);
    return root;
}

DataLine * MachineLearning::meta(Turn T,Result& R)
{
    DataLine * ret = nullptr;
    R = LOST;
    static int depth = 0;
    ++depth;
    Chain lost[40];
    Chain useful[40];
    Chain winner[40];
    Chain * pLost = lost, * pUseful = useful,*pWinner = winner; // pointers
    Step test;
    Node ** setOfStones = (T == YOUR_TURN) ? __collectionOfPlayer : __collectionOfProgram;
    Turn nextTurn = (T == YOUR_TURN) ? MY_TURN : YOUR_TURN;
    for (Node** nextStone = setOfStones; *nextStone; ++nextStone)
    {
        for (int direction = 0; direction < 8; ++direction)
        {
            if (Step::createStep(nextStone,direction,test) == false )
            {
                continue;
            }
            const unsigned char token = direction + (nextStone - setOfStones) * 8;
            test.setToken(token);
            if (isWinnerStep(test))
            {
                *(pWinner++) = Chain(token,nullptr);
            }
            __learningHistory.storeStep(test);
            Result tip;
            DataLine * pNext = nullptr;
            if (depth < _metaDepth)
            {
                pNext = meta(nextTurn,tip);
            }
            else
            {
                tip = seek(nextTurn,_metaForsight,pUseful != useful,test);
            }
            if(tip == UNSURE && __learningHistory.moveHistory(-3).inv( __learningHistory.moveHistory(-1)))
            {
                tip = WON;
            }
            __learningHistory.undoStep();
            switch (tip)
            {
            case UNSURE:
                *(pUseful++) = Chain(token,pNext);
                break;
            case LOST:
                *(pWinner++) = Chain(token,pNext);
                break;
            case WON:
                *(pLost++) = Chain(token,pNext);
                break;
            default:
                break;
            }
        }
    }
    if (depth == 3 )
    {
      CLR();
      show();
    }
    --depth;
    if (pWinner != winner)
    {
        R = WON;
        ret = new DataLine(winner,pWinner - winner, useful, pUseful - useful, lost, pLost - lost);
    }
    else if (pUseful != useful)
    {
        R = UNSURE;
        ret = new DataLine(useful, pUseful - useful, lost, pLost - lost);
    }
    else if (_metaForsight == 1)
    {
        ret = new DataLine(lost,pLost - lost);
    }
    else
    {
        Result tip;
        // --- delete temporary DataLines --- //
        --_metaForsight;
        ret = meta(T,tip);
        ++_metaForsight;
        ret->swapBranches(pLost, pLost - lost);
    }
    return ret;
}
