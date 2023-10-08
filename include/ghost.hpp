#pragma once

#include <queue>
#include <map>
#include <vector>
#include <chrono>
#include <random>

#include "grid.hpp"
#include "moving_object.hpp"

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::system_clock;

class Ghost: public MovingObject {
 public:
  enum class GhostId {
    Red,
    Pink
  };
  enum class GhostState {
    Wandering,
    Hunting,
    RunningAway,
    Reviving
  };
  virtual void Load(std::ifstream& config) final;
  void SetState(const GhostState& new_state);
  GhostId GetType() const;
  GhostState GetState() const;
  void Move(const Grid& grid, const MovingObject& pacman);
  virtual void Reset() final;
  void LevelUp();

 protected:
  void SetTarget(const MovingObject& pacman);
  virtual void SetHuntingTarget(const MovingObject& pacman) = 0;
  void SetWanderingTarget();
  void SetRevivingTarget();
  void ChangeState();
  void SetTargetValue(const Point& target);

  uint32_t move_iterations_;
  Point target_;
  GhostId type_;
  int64_t hunting_period_time_;
  int64_t wandering_period_time_;
  int64_t running_period_time_;
  int64_t hunting_period_change_;
  int64_t wandering_period_change_;
  int64_t running_period_change_;
  int64_t wandering_period_limit_;
  int64_t running_period_limit_;
  GhostState cur_state_;
  int64_t timer_;
  int64_t cur_state_time_;
  std::vector<Point> wandering_targets_;

  std::random_device rd_;
  std::mt19937 gen_;
  std::uniform_int_distribution<> target_distrib_;
  bool is_loading_;
};