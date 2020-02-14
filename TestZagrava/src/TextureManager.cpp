#include "TextureManager.h"

TextureManager* TextureManager::s_Instance = 0;

#include <Shlwapi.h>
#pragma comment(lib, "shlwapi.lib")

TCHAR* GetThisPath(TCHAR* dest, size_t destSize)
{
  if (!dest) return NULL;

  DWORD length = GetModuleFileName(NULL, dest, destSize);
#if (NTDDI_VERSION >= NTDDI_WIN8)
  PathRemoveFileSpec(dest);
#else
  if (MAX_PATH > destSize) return NULL;
  PathRemoveFileSpec(dest);
#endif
  return dest;
}

bool TextureManager::load(const std::string& fileName, const std::string& id, SDL_Renderer* pRenderer)
{
  TCHAR path[1024];
  GetThisPath(path, 1024);
  std::string ex(path);
  ex += fileName;

  SDL_Surface* pTempSurface = IMG_Load(ex.c_str());

  if (pTempSurface == NULL)
  {
    return false;
  }

  SDL_Texture* pTexture = SDL_CreateTextureFromSurface(pRenderer, pTempSurface);

  SDL_FreeSurface(pTempSurface);

  std::map<std::string, SDL_Texture*>::iterator it = m_textureMap.find(id);

  if (pTexture != 0 && it == m_textureMap.end())
  {
    m_textureMap[id] = pTexture;
    return true;
  }

  return false;
}

void TextureManager::draw(const std::string& id, int x, int y, int width, int height, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;
  if (m_currentTexture == nullptr)
    m_currentTexture = m_textureMap[id];

  srcRect.x = 0;
  srcRect.y = 0;
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  SDL_RenderCopy(pRenderer, m_currentTexture, NULL, &destRect);
}

void TextureManager::drawFrame(const std::string& id, int x, int y, int width, int height, float angleRotation, int currentRow, int currentFrame, SDL_Renderer* pRenderer, SDL_RendererFlip flip)
{
  SDL_Rect srcRect;
  SDL_Rect destRect;
  SDL_Point centerPoint;
  if(m_currentTexture == nullptr)
    m_currentTexture = m_textureMap[id];

  srcRect.x = width* currentFrame;
  srcRect.y = height* (currentRow - 1);
  srcRect.w = destRect.w = width;
  srcRect.h = destRect.h = height;
  destRect.x = x;
  destRect.y = y;

  centerPoint.x = width/2;
  centerPoint.y = height/2;  

  SDL_RenderCopyEx(pRenderer, m_currentTexture, &srcRect, &destRect, static_cast<double>(angleRotation), &centerPoint, flip);
}

void TextureManager::clearFromTextureMap(const std::string& id)
{
  m_textureMap.erase(id);
  SDL_DestroyTexture(m_currentTexture);
}