#include "game.h"

Game::Game(const int& S)
  : Board(S)
{
  // --- Collections of stones --- /
  // allocate memory
  __collectionOfPlayer = new Node*[_cols + 1];     /*null-terminated array*/
  __collectionOfProgram = new Node*[_cols + 1];  /*null-terminated array*/
                           // default positions
  reset();
}

void Game::reset()
{
  for (int row = 1; row < _rows + 1; ++row)
  {
    for (int col = 1; col < _cols + 1; ++col)
    {
      __theGrid[row][col].occupied = 0;
    }
  }
  for (int id = 0; id < _cols; ++id)
  {
    __collectionOfPlayer[id] = &__theGrid[1][id + 1];
    __collectionOfPlayer[id]->occupied = -id - 1;
    __collectionOfProgram[id] = &__theGrid[_rows][id + 1];
    __collectionOfProgram[id]->occupied = id + 1;
  }
  // null-terminate arrays for the opponents' stones
  __collectionOfPlayer[_cols] = nullptr;
  __collectionOfProgram[_cols] = nullptr;

  // --- set step stacks for UI -- //
  resetStack();
  srand(time(NULL));
}

bool Game::makeStep(const int& id,const int& dir,Step& step)
{
  Node ** stone = nullptr;
  if (id < 0)
  {
    stone = __collectionOfPlayer - (id + 1);
  }
  return stone ? makeStep(stone,dir,step) : false;
}

bool Game::makeStep(Node ** stone,const int& dir,Step& step)
{
  if ((*stone)->next[dir]->occupied != 0)
  {
    return false;
  }
  step.stone = stone;
  step.place = *stone;
  while (step.place->next[dir]->occupied == 0)
  {
    step.place = step.place->next[dir];
  }
  return true;
}

Game::~Game()
{
}