#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "grid.hpp"
#include "moving_object.hpp"
#include "ghost.hpp"
#include "red_ghost.hpp"
#include "pink_ghost.hpp"
#include "statistics.hpp"

class Logic {
 public:
  enum class Event: int16_t {
    Nothing,
    LevelStarted,
    MoneyEaten,
    GhostEaten,
    PacmanDied,
    GameEnded
  };

  Logic(Statistics& statistics) : statistics_(statistics) {};
  ~Logic();
  void LoadObjects(const std::string& config_file);
  Event Run();
  void Reset();

  Grid::ObjectId GridAt(Point p) const;
  Point GetGridSize() const;
  Point GetPacmanPos() const;
  MovingObject::DirId GetPacmanDirId() const;
  uint32_t GetGhostsCnt() const;
  Ghost::GhostId GetGhostType(uint32_t ind) const;
  Ghost::GhostState GetGhostState(uint32_t ind) const;
  Point GetGhostPos(uint32_t ind) const;
  MovingObject::DirId GetGhostDirId(uint32_t ind) const;
  void SetPacmanDir(MovingObject::DirId dir_id);

 private:
  void ResetMovingObjects();
  void LevelUp();

  Grid grid_;
  MovingObject pacman_;
  Statistics& statistics_;

  std::vector<Ghost*> ghosts_;
};