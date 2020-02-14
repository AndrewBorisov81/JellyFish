#include "Game.h"
#include "PlayState.h"
#include "GameStateMachine.h"

Game* Game::s_instance = 0;

void Game::init(const char* title, int width, int height, bool fullscreen)
{
  int flags = 0;

  if (fullscreen)
  {
    flags = SDL_WINDOW_FULLSCREEN;
  }

  if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
  {
    m_window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
    m_renderer = SDL_CreateRenderer(m_window, -1, 0);
    if (m_renderer)
    {
      SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    }

    m_isRunning = true;
  }
  else {
    throw new std::exception("Fatal");
  }

  m_pGameStateMachine = new GameStateMachine();
  m_pGameStateMachine->pushState(new PlayState());
}

GameStateMachine* Game::getStateMachine()
{
  return m_pGameStateMachine;
}

void Game::handleEvents()
{
  m_pGameStateMachine->handleEvents();

  SDL_Event event;

  SDL_PollEvent(&event);

  switch (event.type)
  {
  case SDL_QUIT:
    m_isRunning = false;
    break;

  default:
    break;
  }
}

void Game::update()
{
  m_pGameStateMachine->update();
}

bool Game::running()
{
  return m_isRunning;
}

void Game::render()
{
  SDL_RenderClear(m_renderer);

  m_pGameStateMachine->render();

   SDL_RenderPresent(m_renderer);
}

void Game::clean()
{
  delete m_pGameStateMachine;

  SDL_DestroyWindow(m_window);
  SDL_DestroyRenderer(m_renderer);
  SDL_Quit();
}

void Game::quit()
{
  m_isRunning = true;
}

SDL_Renderer* Game::getRenderer() const
{
  return m_renderer;
}

SDL_Window* Game::getWindow() const
{
  return m_window;
}
