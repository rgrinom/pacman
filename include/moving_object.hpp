#pragma once

#include <fstream>
#include <iostream>
#include <string>

#include "point.hpp"
#include "grid.hpp"

class MovingObject {
 public:
  enum class DirId: int16_t {
    Left,
    Right,
    Up,
    Down
  };

  MovingObject() = default;
  virtual void Load(std::ifstream& config);
  void SetNextDir(DirId next_dir_id);
  void Move(const Grid& grid);
  Point GetPos() const;
  Point GetDir() const;
  DirId GetDirId() const;
  bool Touches(const Point& obj_pos) const;
  virtual void Reset();

 protected:
  static const double size;

  DirId dir_id_, spawn_dir_id_;
  DirId cur_dir_id_, next_dir_id_;
  Point spawn_pos_;
  Point pos_, dir_;
  double speed_;

  void SetDir(DirId dir_id);
  bool TryMove(const Grid& grid);
};