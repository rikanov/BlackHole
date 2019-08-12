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
#include "machine_learning.h"

//#include "view2d.h"

const int size = 5;

void stopSDL()
{
  //SDL_Quit();
}
int main(int argc,char ** argv)
{
  /*std::atexit(stopSDL);
  Engine board(5, 7);
  View2D teszt("BOARD", 450, 630, board);
  teszt.select();
  return 0;//*/
  for (bool exit = false; !exit;)
  {
    std::cout << "\nDo you want to start the game ? (y / n / e) : ";
    char Q;
    std::cin >> Q;
    if (Q == 'a' || Q == 'A')
    {
      BasicUI teszt(/*size = */ size, /*AI level = */ 8, /*start player ?*/ Q == 'A', /*auto steps ?*/true);
      teszt.start();
    }
    else if(Q == 'p')
    {
        MachineLearning teszt;
        delete teszt.meta(Engine::YOUR_TURN);
        std::cout << std::endl << "max size:  " << DataLine::maxSize() << std::endl;
        std::cout << std::endl << "DLC after deleting root: " << DataLine::counter() << std::endl;
    }
    else if (Q != 'e')
    {
      BasicUI teszt(/*size = */ size, /*AI level = */ 10, /*start player ?*/ Q == 'y');
      teszt.start();
    }
    else
    {
      exit = true;
    }
  }
  return 0;
}
