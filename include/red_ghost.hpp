#pragma once

#include "ghost.hpp"

class RedGhost: public Ghost {
 public:
  RedGhost();
 protected:
  virtual void SetHuntingTarget(const MovingObject& pacman) final;
};