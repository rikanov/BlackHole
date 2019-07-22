#include "sstack.h"

StepStack::StepStack(const int& size)
  :_stackSize(size)
  ,__moveHistory(nullptr)
{
}

void StepStack::resetStack()
{
  // --- set step stacks for UI -- //
  delete[] __moveHistory; // purify it
  __moveHistory = new Step[_stackSize + 1];
  _currentMove = _lastMove = __moveHistory + 1;
  // -------------- //
}

void StepStack::storeStep(Step S)
{
  S.revertableStep();
  *(++_currentMove) = S;
  _lastMove = _currentMove;
}

void StepStack::undoStep()
{
  if (isStarted())
  {
    (_currentMove--)->revertableStep();
  }
}

void StepStack::redoStep()
{
  if ((_currentMove != _lastMove))
  {
    (++_currentMove)->revertableStep();
  }
}

StepStack::~StepStack()
{
  delete[] __moveHistory;
}