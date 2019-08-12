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
    Result dummy;
    DataLine * root = meta(T,dummy);
    std::cout << DataLine::counter() << std::endl;
    __cashedSteps = root;
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
            if (Step::createStep(nextStone,direction,test) == false)
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
            }//*/
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
            if (depth > 2)
                continue;

            std::cout << std::endl;
            for (int i = 0; i < depth; ++i)
                std::cout << '\t';
            if (depth == 1)
            {
                std::cout << "------------------ DLC: ";
                std::cout << DataLine::counter() << std::endl;
                for (int i = 0; i < depth; ++i)
                    std::cout << '\t';
            }

            switch (tip)
            {
            case UNSURE:
                test.printData();
                std::cout << ":\tunsure   " << *pNext << std::flush;
                break;
            case LOST:
                test.printData();
                std::cout << ":\tYou win  " << *pNext << std::flush;
                break;
            case WON:
                test.printData();
                std::cout << ":\tYou lose " << *pNext << std::flush;
                break;
            default:
                break;
            }
            if (depth == 1)
            {
                std::cout << std::endl << std::endl;
            }
        }
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
        for (Chain * next = lost; next != pLost; ++next)
        {
            delete next->getData();
        }
        --_metaForsight;
        ret = meta(T,tip);
        ++_metaForsight;
    }
    return ret;
}
