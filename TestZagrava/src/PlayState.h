#pragma once

#include "SDL.h"
#include "SDL_image.h"
#include <vector>
#include <string>

#include "GameState.h"
#include "Size.h"

//#include "SDLGameObject.h"

class GameObject;
class JellyFish;
class Mover;
class Vector2D;
class Point;

class PlayState : public GameState
{
  static const std::string s_playID;

public:
  virtual void handleEvents();
  virtual void update();
  virtual void render();

  virtual bool onEnter();
  virtual bool onExit();

  virtual std::string getStateID() const { return s_playID; }

private:
  Size m_screenSize;
  Size m_objSize{ 64, 64 };

  int m_mouseX{ 0 };
  int m_mouseY{ 0 };

  bool m_mouseClickDone = false;
  bool m_leftMouseDown = false;
  bool m_objectCreated = false;

public:
  GameObject* createJellyFish(const Point& pos);

  void deleteGameObject(GameObject* gameObject, std::vector<GameObject*> toDeleteGameObjects);

  Vector2D getRandomPoint(const Point& beginPoint, const Size& screenSize, const Size& objectSize);
  GameObject* getHitObject(const Vector2D& pos, const std::vector<GameObject*>& gameObjects);

  bool checkScreenBorders(const Size& screenSize, const Vector2D& objPos, const Size& objectSize);
  bool checkMinDist(const Vector2D& beginPoint, const Vector2D& endPoint, const Size& objectSize);

  void mouseClick(int mouseX, int mouseY);

private:
  std::vector<GameObject*> m_gameObjects;
  std::vector<GameObject*> m_toDeleteGameObjects;
};

