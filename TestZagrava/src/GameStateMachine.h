#pragma once

#include "GameState.h"
#include <vector>

class GameStateMachine
{
  std::vector <GameState*> m_gameStates;
public:
  void pushState(GameState* pState);

  void changeState(GameState* pState);

  void popState();

  void handleEvents();
  void update();
  void render();
};
