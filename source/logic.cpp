#include "../include/logic.hpp"

void Logic::LoadObjects(const std::string& config_file) {
  std::ifstream config;
  config.open("../content/" + config_file);

  std::string source;
  config >> source;
  uint32_t coins_cnt = grid_.Load(source);
  config >> source;
  pacman_.Load(source);
  config >> source;
  statistics_.Load(source, coins_cnt);

  uint32_t ghosts_cnt;
  config >> ghosts_cnt;

  for (int cur_ghost = 0; cur_ghost < ghosts_cnt; ++cur_ghost) {
    uint32_t ghost_type;
    config >> ghost_type;
    if (ghost_type == 0) {
      ghosts_.push_back(new RedGhost());
    }
    config >> source;
    ghosts_.back()->Load(source);
  }

  config.close();
}

void Logic::Run() {
  pacman_.Move(grid_);
  for (auto ghost : ghosts_) {
    ghost->Move(grid_, pacman_.GetPos());
  }

  Point pacman_pos = pacman_.GetPos();
  if (grid_.At(pacman_pos) == Grid::ObjectId::Coin) {
    grid_.Set(pacman_pos, Grid::ObjectId::Nothing);
    statistics_.AddCoinScore();
  }
  for (auto& ghost : ghosts_) {
    if (pacman_.Touches(*ghost)) {
      ResetMovingObjects();
      statistics_.DecreaseLives();
      return;
    }
  }
  if (statistics_.HasWon()) {
    ResetMovingObjects();
    grid_.Reset();
    statistics_.Reset();
    return;
  }
  if (!statistics_.IsAlive()) {
    grid_.Reset();
    statistics_.Reset();
    return;
  }
}

void Logic::ResetMovingObjects() {
  pacman_.Reset();
  for (auto& ghost : ghosts_) {
    ghost->Reset();
  }
}

Grid::ObjectId Logic::GridAt(Point p) const { return grid_.At(p); }
Point Logic::GetGridSize() const { return grid_.GetSize(); }
Point Logic::GetPacmanPos() const { return pacman_.GetPos(); }

void Logic::SetPacmanDir(MovingObject::DirId dir_id) { pacman_.SetNextDir(dir_id); }

uint32_t Logic::GetGhostsCnt() const { return ghosts_.size(); }
Ghost::GhostId Logic::GetGhostType(uint32_t ind) const { return ghosts_[ind]->GetType(); }
Point Logic::GetGhostPos(uint32_t ind) const { return ghosts_[ind]->GetPos(); }