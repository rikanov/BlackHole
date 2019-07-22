#ifndef GAME_HEADER__H
#define GAME_HEADER__H

#include "board.h"
#include "sstack.h"

class Game : public Board,
             public StepStack
{
protected:

  int _numberOfUsableSteps;
  Step __usableSteps[MAX_NUMBER_OF_STONES * 8];
  Step __allowedSteps[MAX_NUMBER_OF_STONES * 8];

public:
  Game(const int& S);
  virtual ~Game();
  void reset();
  bool makeStep(const int& id,const int&,Step&);
  bool makeStep(Node **,const int&,Step&);
};
#endif // !GAME_HEADER__H

