#pragma once

#include <queue>
#include <map>
#include <vector>

#include "grid.hpp"
#include "moving_object.hpp"

class Ghost: public MovingObject {
 public:
  enum class GhostId {
    Red
  };
  GhostId GetType() const;
  void Move(const Grid& grid, Point pacman_pos);

 protected:
  virtual void SetTarget(const Point& pacman_pos) = 0;
  Point target_;
  GhostId type_;
};