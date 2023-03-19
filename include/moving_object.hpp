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
  void Load(const std::string& config_file);
  void SetNextDir(DirId next_dir_id);
  void Move(const Grid& grid);
  Point GetPos() const;
  bool Touches(const MovingObject& obj) const;
  void Reset();

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