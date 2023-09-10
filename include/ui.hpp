#pragma once

#include "logic.hpp"
#include "statistics.hpp"

class UI {
 public:
  enum class Signal: int16_t {
    Nothing,
    WindowClosed,
    Paused,
    Muted,
    NewGame
  };

  UI(Logic& logic, Statistics& statistics);
  virtual Signal Run(const Logic::Event& logic_event) = 0;

 protected:
  Logic& logic_;
  Statistics& statistics_;

  virtual void Draw() = 0;
  virtual Signal CheckClicks() = 0;
};