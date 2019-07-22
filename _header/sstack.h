#ifndef SSTACK__H
#define SSTACK__H

#include "str_step.h"

class StepStack
{
  const int _stackSize;
  // Store steps for UI (undo, redo)
  Step * __moveHistory,*_currentMove,*_lastMove;

public:
  StepStack(const int& S = MAX_NUMBER_OF_MOVES);
  virtual ~StepStack();
  bool isStarted() const {
    return _currentMove != __moveHistory + 1;
  }
  bool isTheLastMove() const {
    return _currentMove == _lastMove;
  }
  int stepCount() const {
    return (_currentMove - __moveHistory);
  }
  const Step& moveHistory(const int& index) const {
    return index < 0 ? *(_currentMove + index + 1) : __moveHistory[index];
  }
  void resetStack();
  void storeStep(Step S);
  void undoStep();
  void redoStep();
};

#endif
