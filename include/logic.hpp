#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "grid.hpp"
#include "moving_object.hpp"
#include "ghost.hpp"
#include "red_ghost.hpp"
#include "statistics.hpp"

class Logic {
 public:
  Logic() = default;
  void LoadObjects(const std::string& config_file);
  void Run();
  void ResetMovingObjects();

  Grid::ObjectId GridAt(Point p) const;
  Point GetGridSize() const;
  Point GetPacmanPos() const;
  uint32_t GetGhostsCnt() const;
  Ghost::GhostId GetGhostType(uint32_t ind) const;
  Point GetGhostPos(uint32_t ind) const;
  void SetPacmanDir(MovingObject::DirId dir_id);

 private:
  Grid grid_;
  MovingObject pacman_;
  Statistics statistics_;

  std::vector<Ghost*> ghosts_;
};