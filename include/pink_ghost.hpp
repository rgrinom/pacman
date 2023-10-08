#pragma once

#include "ghost.hpp"

class PinkGhost: public Ghost {
 public:
  PinkGhost();
 protected:
  virtual void SetHuntingTarget(const MovingObject& pacman) final;
};