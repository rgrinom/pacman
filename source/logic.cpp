#include "../include/logic.hpp"

Logic::~Logic() {
  for (Ghost* ghost : ghosts_) {
    delete ghost;
  }
}

void Logic::LoadObjects(const std::string& config_file) {
  std::ifstream config;
  std::ifstream moving_object_config;
  config.open("../content/configs/" + config_file);

  std::string source;

  config >> source;
  uint32_t coins_cnt = grid_.Load(source);

  config >> source;
  moving_object_config.open("../content/configs/" + source);
  pacman_.Load(moving_object_config);
  moving_object_config.close();

  config >> source;
  statistics_.Load(source, coins_cnt);

  uint32_t ghosts_cnt;
  config >> ghosts_cnt;

  for (int cur_ghost = 0; cur_ghost < ghosts_cnt; ++cur_ghost) {
    uint32_t ghost_type;
    config >> ghost_type;
    if (ghost_type == 0) {
      ghosts_.push_back(new RedGhost());
    } else if (ghost_type == 1) {
      ghosts_.push_back(new PinkGhost());
    }
    config >> source;
    moving_object_config.open("../content/configs/" + source);
    ghosts_.back()->Load(moving_object_config);
    moving_object_config.close();
  }

  config.close();
}

Logic::Event Logic::Run() {
  Event ret = Event::Nothing;
  for (int iteration = 0; iteration < 3; ++iteration) {
    pacman_.Move(grid_);
    for (auto ghost : ghosts_) {
      ghost->Move(grid_, pacman_);
    }
  }

  Point pacman_pos = pacman_.GetPos();
  if (grid_.At(pacman_pos) == Grid::ObjectId::Coin) {
    grid_.Set(pacman_pos, Grid::ObjectId::Nothing);
    statistics_.AddCoinScore();
    ret = Event::MoneyEaten;
  } else if (grid_.At(pacman_pos) == Grid::ObjectId::Buff) {
    grid_.Set(pacman_pos, Grid::ObjectId::Nothing);
    for (auto& ghost : ghosts_) {
      ghost->SetState(Ghost::GhostState::RunningAway);
    }
    ret = Event::MoneyEaten;
  }

  for (auto& ghost : ghosts_) {
    if (pacman_.Touches(ghost->GetPos())) {
      if (ghost->GetState() == Ghost::GhostState::Hunting ||
          ghost->GetState() == Ghost::GhostState::Wandering) {
        ResetMovingObjects();
        statistics_.DecreaseLives();
        return Event::PacmanDied;
      } else if (ghost->GetState() == Ghost::GhostState::RunningAway) {
        ghost->SetState(Ghost::GhostState::Reviving);
        statistics_.AddGhostScore();
        ret = Event::GhostEaten;
      }
    }
  }
  if (statistics_.IsLevelBeaten()) {
    ResetMovingObjects();
    grid_.Reset();
    statistics_.SoftReset();
    LevelUp();
    statistics_.NextLevel();
    return Event::LevelStarted;
  }
  if (!statistics_.IsAlive()) {
    // grid_.Reset();
    // statistics_.HardReset();
    return Event::GameEnded;
  }
  return ret;
}

void Logic::Reset() {
  grid_.Reset();
  statistics_.HardReset();
}

void Logic::ResetMovingObjects() {
  pacman_.Reset();
  for (auto& ghost : ghosts_) {
    ghost->Reset();
  }
}

void Logic::LevelUp() {
  for (Ghost* ghost : ghosts_) {
    ghost->LevelUp();
  }
}

Grid::ObjectId Logic::GridAt(Point p) const { return grid_.At(p); }
Point Logic::GetGridSize() const { return grid_.GetSize(); }
Point Logic::GetPacmanPos() const { return pacman_.GetPos(); }
MovingObject::DirId Logic::GetPacmanDirId() const { return pacman_.GetDirId(); }

void Logic::SetPacmanDir(MovingObject::DirId dir_id) { pacman_.SetNextDir(dir_id); }

uint32_t Logic::GetGhostsCnt() const { return ghosts_.size(); }
Ghost::GhostId Logic::GetGhostType(uint32_t ind) const { return ghosts_[ind]->GetType(); }
Ghost::GhostState Logic::GetGhostState(uint32_t ind) const { return ghosts_[ind]->GetState(); }
Point Logic::GetGhostPos(uint32_t ind) const { return ghosts_[ind]->GetPos(); }
MovingObject::DirId Logic::GetGhostDirId(uint32_t ind) const { return ghosts_[ind]->GetDirId(); }