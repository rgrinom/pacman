#pragma once

#include "logic.hpp"

class UI {
 public:
  UI(Logic& logic_);
  virtual bool Run() = 0;

 protected:
  Logic& logic_;

  virtual void Draw() = 0;
  virtual void DrawGrid() = 0;
  virtual void DrawWall(const Point& pos) = 0;
  virtual void DrawBuff(const Point& pos) = 0;
  virtual void DrawCoin(const Point& pos) = 0;
  virtual void DrawPacman() = 0;
  virtual void DrawGhosts() = 0;
  virtual void DrawRedGhost(const Point& pos) = 0;

  virtual void CheckClicks() = 0;
};