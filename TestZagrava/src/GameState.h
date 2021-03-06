#pragma once

#include <vector>
#include <string>

class GameState
{
protected:
  std::vector<std::string> m_textureIDList;
public:
  virtual void handleEvents() = 0;
  virtual void update() = 0;
  virtual void render() = 0;

  virtual bool onEnter() = 0;
  virtual bool onExit() = 0;

  virtual std::string getStateID() const = 0;
};

