#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <vector>

#include "Size.h"

class GameStateMachine;
class GameObject;
class JellyFish;
class Mover;
class Vector2D;
class Point;

class Game
{
  Game() {}
  ~Game() {}

  static Game* s_instance;

  GameStateMachine* m_pGameStateMachine;

public:
  void init(const char* title, int width, int height, bool fullscreen);

  void handleEvents();
  void update();
  void render();

  bool running();
  void clean();
  void quit();

  SDL_Renderer* getRenderer() const;

  SDL_Window* getWindow() const;

  GameStateMachine* getStateMachine();

  static Game* Instance()
  {
    if (s_instance == 0)
    {
      s_instance = new Game();
      return s_instance;
    }
    return s_instance;
  }

private:
  bool m_isRunning{ false };

  SDL_Window* m_window{ nullptr };
  SDL_Renderer* m_renderer{ nullptr };
};

typedef Game TheGame;