#include "../include/red_ghost.hpp"

RedGhost::RedGhost() { type_ = GhostId::Red; }

void RedGhost::SetTarget(const Point& pacman_pos) {
  target_ = pacman_pos;
  target_ = (floor(target_) + ceil(target_)) / 2;
}