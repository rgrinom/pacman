#pragma once

#include "logic.hpp"

class Sounds {
 public:
  Sounds() : muted_(false) {}
  virtual void Run(const Logic::Event logic_event) = 0;
  virtual void Mute() = 0;

 protected:
  bool muted_;
};