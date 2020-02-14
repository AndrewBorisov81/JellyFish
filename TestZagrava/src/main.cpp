#include "Game.h""

Game *game = nullptr;

const int FPS = 60;
const int FRAME_DELAY = 1000 / FPS;

int main(int argc, char *argv[])
{

  Uint32 frameStart;
  int frameTime;

  game = TheGame::Instance();
  game->init("GameWindow", 1024, 768, false);

  while (game->running())
  {
    frameStart = SDL_GetTicks();

    game->handleEvents();
    game->update();
    game->render();

    frameTime = SDL_GetTicks() - frameStart;

    if (FRAME_DELAY > frameTime) {
      SDL_Delay(FRAME_DELAY - frameTime);
    }
  }

  game->clean();
  return 0;
}
