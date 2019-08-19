#ifndef GLOBAL_CONSTANTS_H
#define GLOBAL_CONSTANTS_H

#include <iostream>      /* for test lines */
#include <sstream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <unistd.h>

#define log(X) std::cout<<(X)<<' '<<std::flush;
#define log2(X,Y) std::cout<<(X)<<' '<<(Y)<<std::endl;
#define log3(X,Y,Z) std::cout<<(X)<<' '<<(Y)<<' '<<(Z)<<std::endl;

static inline void CLR() { std::cout << "\033[2J\033[1;1H" << std::endl;; }
 static inline void Sleep(int m) {sleep(m * 1); }
//#include <Windows.h>
//static inline void CLR() { system("CLS"); };

const int MAX_NUMBER_OF_MOVES = 200;
const int MAX_NUMBER_OF_STONES = 10;
const int MAX_NUMBER_OF_SUGGESTED_STEPS = 10;
const int MAX_HEURISTIC_DEPTH = 10;
const int MAX_DEPTH_OF_CACHE = 3;
const int DEPTH_TO_BUILD_CACHE = 9;
const int WALL = -7;

#endif
