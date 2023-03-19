#pragma once

#include "ghost.hpp"

class RedGhost: public Ghost {
 public:
  RedGhost();
 protected:
  virtual void SetTarget(const Point& pacman_pos) final;
};