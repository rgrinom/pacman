#include "../include/red_ghost.hpp"

RedGhost::RedGhost() { type_ = GhostId::Red; }

void RedGhost::SetHuntingTarget(const MovingObject& pacman) {
  SetTargetValue(pacman.GetPos());
}