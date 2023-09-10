#include "../include/pink_ghost.hpp"

PinkGhost::PinkGhost() { type_ = GhostId::Pink; }

void PinkGhost::SetHuntingTarget(const MovingObject& pacman) {
  SetTargetValue(pacman.GetPos() + pacman.GetDir() * 2);
}