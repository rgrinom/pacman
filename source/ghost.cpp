#include "../include/ghost.hpp"

void Ghost::Load(std::ifstream& config) {
  is_loading_ = true;
  MovingObject::Load(config);

  config >> hunting_period_time_;
  config >> wandering_period_time_;
  config >> running_period_time_;

  config >> hunting_period_change_;
  config >> wandering_period_change_;
  config >> running_period_change_;

  config >> wandering_period_limit_;
  config >> running_period_limit_;

  uint32_t wandering_targets_cnt_;
  config >> wandering_targets_cnt_;
  wandering_targets_ = std::vector<Point>(wandering_targets_cnt_);
  for (Point& target : wandering_targets_) {
    config >> target;
  }
  gen_ = std::mt19937(rd_());
  target_distrib_ = std::uniform_int_distribution<>(0, wandering_targets_cnt_ - 1);

  SetState(GhostState::Wandering);
  is_loading_ = false;
}

void Ghost::Reset() {
  MovingObject::Reset();
  if (!is_loading_) {
    SetState(GhostState::Wandering);
  }
}

void Ghost::LevelUp() {
  hunting_period_time_ += hunting_period_change_;
  wandering_period_time_ -= wandering_period_change_;
  wandering_period_time_ = std::max(wandering_period_time_, wandering_period_limit_);
  running_period_time_ -= running_period_change_;
  running_period_time_ = std::max(running_period_time_, running_period_limit_);
}

void Ghost::SetState(const GhostState& new_state) {
  cur_state_ = new_state;
  if (cur_state_ == GhostState::Wandering) {
    cur_state_time_ = wandering_period_time_;
    move_iterations_ = 2;
    SetTargetValue(wandering_targets_[target_distrib_(gen_)]);
  } else if (cur_state_ == GhostState::Hunting) {
    cur_state_time_ = hunting_period_time_;
    move_iterations_ = 2;
  } else if (cur_state_ == GhostState::RunningAway) {
    cur_state_time_ = running_period_time_;
    move_iterations_ = 1;
    SetTargetValue(wandering_targets_[target_distrib_(gen_)]);
  } else if (cur_state_ == GhostState::Reviving) {
    move_iterations_ = 5;
    SetTargetValue(spawn_pos_);
    return;
  }
  timer_ = 0;
}

void Ghost::ChangeState() {
  if (cur_state_ == GhostState::Reviving) {
    if (Touches(target_)) {
      SetState(GhostState::Hunting);
    }
    return;
  }
  if (timer_ < cur_state_time_) {
    return;
  }
  if (cur_state_ == GhostState::Wandering) {
    SetState(GhostState::Hunting);
  } else if (cur_state_ == GhostState::Hunting) {
    SetState(GhostState::Wandering);
  } else if (cur_state_ == GhostState::RunningAway) {
    SetState(GhostState::Hunting);
  }
}

Ghost::GhostId Ghost::GetType() const { return type_; }
Ghost::GhostState Ghost::GetState() const { return cur_state_; }

void Ghost::SetTarget(const MovingObject& pacman) {
  if (cur_state_ == GhostState::Hunting) {
    SetHuntingTarget(pacman);
  } else if (cur_state_ != GhostState::Reviving) {
    SetWanderingTarget();
  }
}

void Ghost::SetWanderingTarget() {
  while (Touches(target_)) {
    SetTargetValue(wandering_targets_[target_distrib_(gen_)]);
  }
}

void Ghost::SetTargetValue(const Point& target) {
  target_ = target;
  target_ = (floor(target_) + ceil(target_)) / 2;
}

void Ghost::Move(const Grid& grid, const MovingObject& pacman) {
  for (uint32_t iteration = 0; iteration < move_iterations_; ++iteration) {
    ChangeState();
    SetTarget(pacman);
    Point my_pos = (floor(pos_) + ceil(pos_)) / 2;

    if (target_.x < 0) {
      target_.x += grid.GetSize().x;
    } else if (target_.x >= grid.GetSize().x) {
      target_.x -= grid.GetSize().x;
    }
    if (target_.y < 0) {
      target_.y += grid.GetSize().y;
    } else if (target_.y >= grid.GetSize().y) {
      target_.y -= grid.GetSize().y;
    }
    std::vector<std::vector<bool>> visited(grid.GetSize().y,
                                          std::vector<bool>(grid.GetSize().x, 0));
    std::queue<Point> bfs_points;
    bfs_points.push(target_);
    visited[target_.y][target_.x] = true;
    std::vector<Point> shifts = {Point(-1,  0),
                                Point( 1,  0),
                                Point( 0, -1),
                                Point( 0,  1)};
    try {
      while (!bfs_points.empty()) {
        Point cur_p = bfs_points.front();
        bfs_points.pop();
        for (uint32_t i = 0; i < shifts.size(); ++i) {
          Point next_p = cur_p + shifts[i];
          if (next_p.y < 0 || next_p.y > grid.GetSize().y) {
            continue;
          }
          if (next_p.x < 0 || next_p.x > grid.GetSize().x) {
            continue;
          }
          if (grid.At(next_p) == Grid::ObjectId::Wall) {
            continue;
          }
          if (visited[next_p.y][next_p.x]) {
            continue;
          }
          if (next_p == my_pos) {
            if (i == 0) {
              SetNextDir(DirId::Right);
            } else if (i == 1) {
              SetNextDir(DirId::Left);
            } else if (i == 2) {
              SetNextDir(DirId::Down);
            } else if (i == 3) {
              SetNextDir(DirId::Up);
            }
            throw 1;
          }
          visited[next_p.y][next_p.x] = true;
          bfs_points.push(next_p);
        }
      }
    } catch (...) {

    }


    MovingObject::Move(grid);
    ++timer_;
  }
}