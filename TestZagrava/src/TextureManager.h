#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <map>

class TextureManager
{
  std::map<std::string, SDL_Texture*> m_textureMap;
  SDL_Texture* m_currentTexture{ nullptr };

  static TextureManager* s_Instance;

  TextureManager() {}
  ~TextureManager() {}

public:

  bool load(const std::string& fileName, const std::string& id, SDL_Renderer* pRenderer);

  void draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer *pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  void drawFrame(const std::string& id, int x, int y, int width, int height, float angleRotation, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip = SDL_FLIP_NONE);

  static TextureManager* Instance()
  {
    if (s_Instance == NULL)
    {
      s_Instance = new TextureManager();
      return s_Instance;
    }
    return s_Instance;
  }

  void clearFromTextureMap(const std::string& id);
};
typedef TextureManager TheTextureManager;